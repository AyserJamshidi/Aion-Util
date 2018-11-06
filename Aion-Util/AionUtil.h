#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AionUtil.h"

#include <Windows.h>
#include <QSystemTrayIcon>
#include <QGroupBox>
#include <QLabel>
#include <QCheckBox>
#include <QCloseEvent>
#include <QAction>
#include <QMenu>

class AionUtil : public QMainWindow {
	Q_OBJECT

public:
	AionUtil(QWidget *parent = Q_NULLPTR);

protected:
	void closeEvent(QCloseEvent *event) override;

private:
	Ui::AionUtilClass ui;

	void AionLoop();
	void createActions();
	void createTrayIcon();
	void peacefulQuit();
	int StartProgram(LPCTSTR lpApplicationName, LPWSTR argv);

	QGroupBox *iconGroupBox;
	QLabel *iconLabel;
	QCheckBox *showIconCheckBox;

	QSystemTrayIcon *trayIcon;
	QMenu *trayIconMenu;

	QAction *hideAction;
	QAction *unhideAction;
	QAction *quitAction;
};
