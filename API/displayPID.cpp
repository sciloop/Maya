//
// creator : sciloop
//
// Get the process ID of Maya
// and display it in the main menu and the output window.

#include <afxwin.h>
#include <maya/MGlobal.h>
#include <maya/MFnPlugin.h>
#include <maya/MPxCommand.h>


//________________________________________________________________________________
//
//
class displayPID : public MPxCommand
{
public:
					displayPID() {};
	virtual MStatus	doIt ( const MArgList & );
	static void*	creator();
};

//________________________________________________________________________________
//
//
void* displayPID::creator()
{return new displayPID;}

//________________________________________________________________________________
//
//
MStatus initializePlugin( MObject _obj )
{
	MFnPlugin	plugin( _obj, "sciloop", "1.0", "Any" );
	MStatus		stat;

	stat = plugin.registerCommand(	"displayPID",
									displayPID::creator );

	if ( !stat )
	{stat.perror( "registerCommand" );}

	else
	{
		MGlobal::displayInfo( " sciloop message: c++ API:"
								" command: 'displayPID' loaded." );
	}

	return stat;
}

//________________________________________________________________________________
//
//
MStatus uninitializePlugin( MObject obj )
{
	MFnPlugin	plugin( obj );
	MStatus		stat;
	stat = plugin.deregisterCommand( "displayPID" );

	if ( !stat )
	{stat.perror( "deregisterCommand" );}

	else
	{
		MGlobal::displayInfo( " sciloop message: c++ API:"
								" command: 'displayPID' unloaded." );
	}

	return stat;
}


//________________________________________________________________________________
//
//
MStatus displayPID::doIt( const MArgList & args )
{

	MStatus stat;
	MString commandString;
	commandString += " int $pid = getpid();";
	commandString += " string $pidStr = \"pid: \" + $pid;";
	commandString += " string $pidMenu = `menu -parent $gMainWindow -enable false";
	commandString += "-tearOff false -aob false -label $pidStr`;";
	stat = MGlobal::executeCommand( commandString );

	HWND wh;
	CWnd theWindow;
	CWnd *h;
	CEdit editCtrl;

	if( (wh = FindWindow( nullptr, L"Output Window" ))==nullptr )
	{return MS::kFailure;}

	if( !theWindow.Attach( wh ) )
	{return MS::kFailure;}

	if( (h = theWindow.GetTopWindow())!=nullptr )
	{
		MString outputWindowStr = "Output Window   Maya PID : ";
		outputWindowStr = outputWindowStr + GetCurrentProcessId();
		SetWindowText( wh, outputWindowStr.asWChar() );
	}
	else
	{return MS::kFailure;}

	theWindow.Detach();
	editCtrl.Detach();

	return MS::kSuccess;
}

//________________________________________________________________________________
//
//



