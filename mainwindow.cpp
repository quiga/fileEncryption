//			###############################################################################
//			##
//			##	
//			##			Filename:  	mainwindow.cpp
//			##			Classname: 	MainWindow
//			##			
//			##			Author: 	quiga	
//			##			Copyright 2014
//			##

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
