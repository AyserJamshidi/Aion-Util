#include "AionUtil.h"

#include <QDebug>
#include <QThread>
#include <QtConcurrent/qtconcurrentrun.h>
//#include <locale>
//#include <codecvt>
//#include <algorithm>

#include "Util/cmdLine.h"
#include "Util/StringTools.h"

bool keepLooping = true;
std::vector<int> ignoredPids;

void AionUtil::AionLoop() {
	cmdLine commandLineQuery = cmdLine();
	StringTools strTools = StringTools();
	std::vector<std::wstring> commandLineInfo;
	HANDLE oldAion;

	while(keepLooping) {
		commandLineInfo = commandLineQuery.GetCommandLines();
		int setPid = 0;
		std::wstring aionPath;
		std::wstring parameters;

		for(std::wstring wStr : commandLineInfo) {
			// If Pid isn't set, then set and cont...
			if(strTools.isOnlyNumeric(wStr)) {
				setPid = std::stoi(wStr);
				continue;
			}
			
			if(std::find(ignoredPids.begin(), ignoredPids.end(), setPid) != ignoredPids.end()) {
				//setPid = 0;
				continue;
			}

			// If aionPath isn't set, then set...
			if(aionPath.size() <= 0) {
				aionPath = wStr.substr(0, wStr.find(L" -ip:"));
			}

			// Prereqs complete, time to set parameter and start game...
			parameters = wStr.substr(wStr.find(L"-ip:"));

			qDebug() << "\n2 = " << aionPath << "\n3 = " << parameters;

			oldAion = OpenProcess(PROCESS_ALL_ACCESS, false, setPid);

			if(!TerminateProcess(oldAion, 1)) {
				qDebug() << "An error occured while trying to close Aion.";
				break;
			}

			CloseHandle(oldAion);
			int newAionPid = StartProgram(aionPath.c_str(), (LPWSTR)parameters.c_str());

			ignoredPids.push_back(newAionPid);
			qDebug() << newAionPid << " successfully started and added to ignore list.";
		}
		QThread::msleep(1500);
	}
	commandLineQuery.cleanUp();
}

AionUtil::AionUtil(QWidget *parent) : QMainWindow(parent) {
	createActions();
	createTrayIcon();

	ui.setupUi(this);

	QFuture<void> t1 = QtConcurrent::run(this, &AionUtil::AionLoop);
}

void AionUtil::createActions() {
	hideAction = new QAction("Hide", this);
	connect(hideAction, &QAction::triggered, this, &QWidget::hide);

	unhideAction = new QAction(tr("Restore"), this);
	connect(unhideAction, &QAction::triggered, this, &QWidget::showNormal);

	quitAction = new QAction(tr("Quit"), this);
	connect(quitAction, &QAction::triggered, this, &AionUtil::peacefulQuit);
}

void AionUtil::createTrayIcon() {
	trayIconMenu = new QMenu(this);
	trayIconMenu->addAction(hideAction);
	trayIconMenu->addAction(unhideAction);
	trayIconMenu->addSeparator();
	trayIconMenu->addAction(quitAction);

	trayIcon = new QSystemTrayIcon(this);
	trayIcon->setContextMenu(trayIconMenu);

	QIcon icon = QIcon(":/AionUtil/Resources/Images/AionLogo.png");
	trayIcon->setIcon(icon);
	setWindowIcon(icon);

	trayIcon->setToolTip("Lmfaoown\'s Aion Utility");
	trayIcon->setVisible(true);
}

void AionUtil::closeEvent(QCloseEvent *event) {
	hide();
	event->ignore();
}

void AionUtil::peacefulQuit() {
	keepLooping = false;
	QApplication::quit();
}

int AionUtil::StartProgram(LPCTSTR lpApplicationName, LPWSTR argv) {
	// additional information
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	// set the size of the structures
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	// start the program up
	bool bSuccess = CreateProcess(lpApplicationName,   // the path
				  argv,			  // Command line
				  FALSE,           // Process handle not inheritable
				  FALSE,           // Thread handle not inheritable
				  FALSE,          // Set handle inheritance to FALSE
				  FALSE,           // No creation flags
				  FALSE,           // Use parent's environment block
				  FALSE,           // Use parent's starting directory 
				  &si,            // Pointer to STARTUPINFO structure
				  &pi             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
	);

	int processId;

	if(bSuccess) {
		processId = GetProcessId(pi.hProcess);
	}
	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return processId;
}