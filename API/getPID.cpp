//
// creator : sciloop
//
// Get the process ID of Maya
// and display it in the output window.

#include <afxwin.h>
#include <maya/MGlobal.h>
#include <maya/MFnPlugin.h>
#include <maya/MPxCommand.h>


//________________________________________________________________________________
//
//
class getPID : public MPxCommand
{
public:
					getPID() {};
	virtual MStatus	doIt ( const MArgList& );
	static void*	creator();
};

//________________________________________________________________________________
//
//
void* getPID::creator()
{return new getPID;}

//________________________________________________________________________________
//
//
MStatus initializePlugin( MObject _obj )
{
	MFnPlugin	plugin( _obj, "sciloop", "1.0", "Any" );
	MStatus		stat;

	stat = plugin.registerCommand(	"getPID",
									getPID::creator );

	if ( !stat )
	{stat.perror( "registerCommand" );}

	else
	{
		MGlobal::displayInfo( " sciloop message: c++ API:"
								" command: 'getPID' loaded." );
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
	stat = plugin.deregisterCommand( "getPID" );

	if ( !stat )
	{stat.perror( "deregisterCommand" );}

	else
	{
		MGlobal::displayInfo( " sciloop message: c++ API:"
								" command: 'getPID' unloaded." );
	}

	return stat;
}


//________________________________________________________________________________
//
//
MStatus getPID::doIt( const MArgList & args )
{

	MStatus stat;
	MString commandString;
	commandString += " int $pid = `getpid`;";
	commandString += " string $pidStr = \"pid: \" + $pid;";
	commandString += " string $pidMenu = `menu -parent $gMainWindow -enable false";
	commandString += "-tearOff false -aob false -label $pidStr`;";
	stat = MGlobal::executeCommand( commandString );

	HWND wh;
	CWnd theWindow, *h;
	CEdit editCtrl;

	if( (wh = FindWindow( NULL, "Output Window" ))==NULL )
	{return MS::kFailure;}

	if( !theWindow.Attach( wh ) )
	{return MS::kFailure;}

	if( (h = theWindow.GetTopWindow())!=NULL )
	{
		MString outputWindowStr = "Output Window   Maya PID : ";
		outputWindowStr = outputWindowStr + GetCurrentProcessId();
		SetWindowText( wh,_T( outputWindowStr.asChar() ) );
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



