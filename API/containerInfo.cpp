//
//

#include <maya/MPxNode.h>
#include <maya/MFnPlugin.h>
#include <maya/MGlobal.h>

//____________________________________________________________________________
//
//
class containerInfo : public MPxNode
{
public:
						containerInfo(){};
	virtual				~containerInfo(){};

	static  void*		creator();
	static  MStatus		initialize();

	static	MTypeId id;

};

//____________________________________________________________________________
//
//
MTypeId containerInfo::id = 0x55;

//____________________________________________________________________________
//
//
void* containerInfo::creator()
{return new containerInfo();}

//____________________________________________________________________________
//
//
MStatus containerInfo::initialize()
{return MS::kSuccess ;}

//____________________________________________________________________________
//
//
MStatus initializePlugin(MObject obj)
{
	MStatus   stat;
	MFnPlugin plugin(obj, "sciloop", "1.0", "Any");

	stat = plugin.registerNode(	"containerInfo",
								containerInfo::id,
								containerInfo::creator,
								containerInfo::initialize );

	if( !stat ) 
	{
		stat.perror( "registerNode" );
		return stat;
	}
	else
	{
		MGlobal::displayInfo(	" sciloop message: c++ API: nodeType:"
								" 'containerInfo' loaded." );
	}

	return stat;
}

//________________________________________________________________________
//
//
MStatus uninitializePlugin(MObject obj)
{
	MStatus   stat;
	MFnPlugin plugin(obj);

	stat = plugin.deregisterNode( containerInfo::id );

	if( !stat ) 
	{
		stat.perror( "deregisterNode" );
		return stat;
	}
	else
	{
		MGlobal::displayInfo(	" sciloop message: c++ API: nodeType:"
								" 'containerInfo' unloaded." );
	}

	return stat;
}

//________________________________________________________________________
//
//




