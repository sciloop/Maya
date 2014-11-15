//
//

#include <maya/MPxTransform.h>
#include <maya/MPxTransformationMatrix.h>
#include <maya/MGlobal.h>
#include <maya/MFnPlugin.h>

//__________________________________________________________________________
//
// 
class sceneInfoMatrix : public MPxTransformationMatrix
{

public:
							sceneInfoMatrix(){};
							~sceneInfoMatrix(){};
	static void*			creator();

	static MTypeId			id;
};

//__________________________________________________________________________
//
//
class sceneInfo : public MPxTransform
{

public:
	sceneInfo();
	sceneInfo(MPxTransformationMatrix *);
	virtual								~sceneInfo();
	virtual MPxTransformationMatrix*	createTransformationMatrix();
	virtual void						postConstructor();

	sceneInfoMatrix*					getSceneInfoTransformMatrix();

	static void *						creator();
	static MStatus						initialize();

	static MTypeId						id;
};



//__________________________________________________________________________
//
//
MTypeId sceneInfo::id(0x56);
MTypeId sceneInfoMatrix::id(0x57);


//__________________________________________________________________________
//
//
void *sceneInfoMatrix::creator()
{return new sceneInfoMatrix();}

//__________________________________________________________________________
//
//
sceneInfo::sceneInfo() : MPxTransform()
{}

//__________________________________________________________________________
//
//
sceneInfo::sceneInfo( MPxTransformationMatrix *tm ) : MPxTransform( tm )
{}

//__________________________________________________________________________
//
//
sceneInfo::~sceneInfo()
{}

//__________________________________________________________________________
//
// Post constructor  
//
void sceneInfo::postConstructor()
{	
	MPxTransform::postConstructor();
	
	if( nullptr==baseTransformationMatrix )
	{
		MGlobal::displayWarning( "sceneInfo: NULL baseTransformationMatrix found!" );
		baseTransformationMatrix = new MPxTransformationMatrix();
	}
}

//__________________________________________________________________________
//
//
MPxTransformationMatrix* sceneInfo::createTransformationMatrix()
{return new sceneInfoMatrix();}

//__________________________________________________________________________
//
//
void* sceneInfo::creator()
{return new sceneInfo();}

//__________________________________________________________________________
//
//
MStatus sceneInfo::initialize()
{return MS::kSuccess;}

//__________________________________________________________________________
//
// Return transformation matrix.
//
sceneInfoMatrix* sceneInfo::getSceneInfoTransformMatrix()
{

	sceneInfoMatrix* ltm = ( sceneInfoMatrix* ) baseTransformationMatrix;
	return ltm;
}

//__________________________________________________________________________
//
//
MStatus initializePlugin( MObject obj )
{
	MStatus   stat;
	MFnPlugin plugin( obj, "sciloop", "1.0", "Any" );

	const MString classification = "drawdb/geometry/transform";

	stat = plugin.registerTransform(	"sceneInfo",
										sceneInfo::id,
										&sceneInfo::creator,
										&sceneInfo::initialize,
										&sceneInfoMatrix::creator,
										sceneInfoMatrix::id,
										&classification );

	if( !stat ) 
	{
		stat.perror( "registerNode" );
		return stat;
	}
	else
	{
		MGlobal::displayInfo(	" sciloop message: c++ API: nodeType:"
								" 'sceneInfo' loaded.");
	}

	return stat;
}

//__________________________________________________________________
//
//
MStatus uninitializePlugin( MObject obj )
{
	MStatus   stat;
	MFnPlugin plugin(obj);
	stat = plugin.deregisterNode( sceneInfo::id );

	if( !stat ) 
	{
		stat.perror( "deregisterNode" );
		return stat;
	}
	else
	{
		MGlobal::displayInfo(	" sciloop message: c++ API: nodeType:"
								" 'sceneInfo' unloaded." );
	}

	return stat;
}

//___________________________________________________________________
//
//
