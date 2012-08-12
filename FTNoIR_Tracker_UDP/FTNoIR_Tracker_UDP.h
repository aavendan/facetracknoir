#include "..\ftnoir_tracker_base\ftnoir_tracker_base.h"
#include "ui_FTNoIR_FTNClientcontrols.h"
#include <QThread>
#include <QUdpSocket>
#include <QMessageBox>
#include <QSettings>
#include <windows.h>
#include "math.h"

class FTNoIR_Tracker : public ITracker, QThread
{
public:
	FTNoIR_Tracker();
	~FTNoIR_Tracker();

	void Release();
    void Initialize( QFrame *videoframe );
    void StartTracker( HWND parent_window );
    void StopTracker( bool exit );
	bool GiveHeadPoseData(THeadPoseData *data);
	void loadSettings();

	void getFullName(QString *strToBeFilled);
	void getShortName(QString *strToBeFilled);
	void getDescription(QString *strToBeFilled);

protected:
	void run();												// qthread override run method

private:
	// Handles to neatly terminate thread...
	HANDLE m_StopThread;
	HANDLE m_WaitThread;

	// UDP socket-variables
	QUdpSocket *inSocket;									// Receive from ...
	QUdpSocket *outSocket;									// Send to ...
	QHostAddress destIP;									// Destination IP-address
	int destPort;											// Destination port-number
	QHostAddress srcIP;										// Source IP-address
	int srcPort;											// Source port-number

	THeadPoseData newHeadPose;								// Structure with new headpose

	////parameter list for the filter-function(s)
	//enum
	//{
	//	kPortAddress=0,										// Index in QList
	//	kNumFilterParameters								// Indicate number of parameters used
	//};
	//QList<std::pair<float,float>>	parameterRange;
	//QList<float>					parameterValueAsFloat;

	float portAddress;										// Port-number
	QString trackerFullName;								// Trackers' name and description
	QString trackerShortName;
	QString trackerDescription;
};

// Widget that has controls for FTNoIR protocol client-settings.
class TrackerControls: public QWidget, Ui::UICFTNClientControls, public ITrackerDialog
{
    Q_OBJECT
public:

	explicit TrackerControls();
    virtual ~TrackerControls();
	void showEvent ( QShowEvent * event );

	void Release();											// Member functions which are accessible from outside the DLL
    void Initialize(QWidget *parent);

	void getFullName(QString *strToBeFilled);
	void getShortName(QString *strToBeFilled);
	void getDescription(QString *strToBeFilled);
	void getIcon(QIcon *icon);

private:
	Ui::UICFTNClientControls ui;
	void loadSettings();
	void save();

	/** helper **/
	bool settingsDirty;

	QString trackerFullName;								// Trackers' name and description
	QString trackerShortName;
	QString trackerDescription;

private slots:
	void doOK();
	void doCancel();
	void settingChanged() { settingsDirty = true; };
};


