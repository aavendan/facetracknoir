/********************************************************************************
* FaceTrackNoIR		This program is a private project of some enthusiastic		*
*					gamers from Holland, who don't like to pay much for			*
*					head-tracking.												*
*																				*
* Copyright (C) 2010-2011	Wim Vriend (Developing)								*
*							Ron Hendriks (Researching and Testing)				*
*																				*
* Homepage																		*
*																				*
* This program is free software; you can redistribute it and/or modify it		*
* under the terms of the GNU General Public License as published by the			*
* Free Software Foundation; either version 3 of the License, or (at your		*
* option) any later version.													*
*																				*
* This program is distributed in the hope that it will be useful, but			*
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY	*
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for	*
* more details.																	*
*																				*
* You should have received a copy of the GNU General Public License along		*
* with this program; if not, see <http://www.gnu.org/licenses/>.				*
*																				*
* FSUIPCServer		FSUIPCServer is the Class, that communicates headpose-data	*
*					to games, using the FSUIPC.dll.			         			*
********************************************************************************/
#pragma once
#ifndef INCLUDED_FSUIPCSERVER_H
#define INCLUDED_FSUIPCSERVER_H

#include "Windows.h"
#include <stdlib.h>
#include "FSUIPC_User.h"

#include "..\ftnoir_protocol_base\ftnoir_protocol_base.h"
#include "ui_FTNoIR_FSUIPCcontrols.h"
#include <QMessageBox>
#include <QSettings>
#include <QLibrary>
#include <QProcess>
#include <QDebug>
#include <QFile>
#include <QFileDialog>

static const char* FSUIPC_FILENAME = "C:\\Program Files\\Microsoft Games\\Flight Simulator 9\\Modules\\FSUIPC.dll";

//
// Define the structures necessary for the FSUIPC_Write calls
//
#pragma pack(push,1)		// All fields in structure must be byte aligned.
typedef struct
{
 int Control;				// Control identifier
 int Value;					// Value of DOF
} TFSState;
#pragma pack(pop)

class FTNoIR_Protocol_FSUIPC : public IProtocol
{
public:
	FTNoIR_Protocol_FSUIPC();
	~FTNoIR_Protocol_FSUIPC();

	void Release();
    void Initialize();

	bool checkServerInstallationOK( HANDLE handle );
	void sendHeadposeToGame( T6DOF *headpose );

private:
	// Private properties
	QString ProgramName;
	QLibrary FSUIPCLib;
	QString LocationOfDLL;
	float prevPosX, prevPosY, prevPosZ, prevRotX, prevRotY, prevRotZ;

	static int scale2AnalogLimits( float x, float min_x, float max_x );
	void loadSettings();
};

// Widget that has controls for FTNoIR protocol client-settings.
class FSUIPCControls: public QWidget, Ui::UICFSUIPCControls, public IProtocolDialog
{
    Q_OBJECT
public:

	explicit FSUIPCControls();
    virtual ~FSUIPCControls();
	void showEvent ( QShowEvent * event );

	void Release();											// Member functions which are accessible from outside the DLL
    void Initialize(QWidget *parent);

private:
	Ui::UICFSUIPCControls ui;
	void loadSettings();
	void save();

	/** helper **/
	bool settingsDirty;

private slots:
	void doOK();
	void doCancel();
	void settingChanged() { settingsDirty = true; };
	void getLocationOfDLL();
};

#endif//INCLUDED_FSUIPCSERVER_H
//END
