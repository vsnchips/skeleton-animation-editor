//---------------------------------------------------------------------------
//***
//*** This is an annotated version of a file from the COMP308 assignment on
//*** which we based the 2018 CGRA350 assignment 2.
//*** 
//*** 
//*** This file contains a parser for the ASF file format.
//***
//***
//*** All annotations are on lines that start with the five characters //***
//***
//*** The COMP308 assignment was expected to be completed in legacy OpenGL;
//*** the CGRA350 assignment is expected to be completed in modern OpenGL.
//***
//***
//*** Create a new skeleton by code like this:
//***   Skeleton *my_skeleton = nullptr;
//***   my_skeleton = new Skeleton(filename);
//***
//*** Render a skeleton using this command:
//***   my_skeleton->renderSkeleton();
//***
//*** Neil Dodgson, 26 August 2018
//***
//---------------------------------------------------------------------------
//
// Copyright (c) 2016 Taehyun Rhee, Joshua Scott, Ben Allen
//
// This software is provided 'as-is' for assignment of COMP308 in ECS,
// Victoria University of Wellington, without any express or implied warranty. 
// In no event will the authors be held liable for any damages arising from
// the use of this software.
//
// The contents of this file may not be copied or duplicated in any form
// without the prior permission of its owner.
//
//----------------------------------------------------------------------------

#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>


//*** COMP308 had its own math and geometry libraries. CGRA350 students are 
//*** expected to use GLM for their mathematics and create their own sphere,
//*** cylinder and cone objects, either by creating them as for the sphere in
//*** assignment 1 or by reading them in from a file (which will require
//*** writing or finding code to read a geometry file).

#include "opengl.hpp"
#include "skeleton.hpp"

#include <glm/glm.hpp>

using namespace std;
using namespace glm;

Skeleton::Skeleton(string filename) {
	bone b = bone();
	b.name = "root";
	b.freedom |= dof_rx;
	b.freedom |= dof_ry;
	b.freedom |= dof_rz;
	b.freedom |= dof_root;
	b.freedom == 0;
	m_bones.push_back(b);
	bonemap[b.name] = &b;
	readASF(filename);
}

void Skeleton::setProgram(cgra::Program & prog){
	m_program = & prog;
}

void Skeleton::defaultBoneMesh(cgra::Mesh * d){
	//for (bone b : m_bones ){ b.boneMesh=d;}
	for (int i=0; i<m_bones.size(); i++){
		//m_bones.at(i).boneMesh=d;
	}
}
//-------------------------------------------------------------
// [Assignment 2] :
// You may need to revise this function for Completion/Challenge
//-------------------------------------------------------------
void Skeleton::renderSkeleton( cgra::Mesh * placeholderbone) {

	m_program->use();
	//*** glMatrixMode is a deprecated function that should
	//*** not be used in modern OpenGL - you need to manage
	//*** your matrices yourself
	//glMatrixMode(GL_MODELVIEW);

	//*** glPushMatrix is a deprecated function that you will
	//*** not use in modern OpenGL because modern OpenGL expects
	//*** you to manage the matrices yourself
	//glPushMatrix();

	//Actually draw the skeleton
	mat4 at(1.0f);
	mat4 ar(1.0f);

	renderBone(at,ar,&m_bones[0], placeholderbone);

	// Clean up
	//*** glPopMatrix is a deprecated function that is the
	//*** partner of glPushMatrix (see above)
	//glPopMatrix();
}


//-------------------------------------------------------------
// [Assignment 2] :
// Should render each bone by drawing the axes, and the bone
// then translating to the end of the bone and drawing each
// of it's children. Remember to use the basis rotations
// before drawing the axes (and for Completion, rotation).
// The actual bone is NOT drawn with the basis rotation.
//
// Should not draw the root bone (because it has zero length)
// but should go on to draw it's children
//-------------------------------------------------------------
void Skeleton::renderBone(mat4 & accumT, mat4 & accumR, bone *b,cgra::Mesh * placeholderbone) {

	//animation first. The bone's own animation affects the bones orientation,
	//and the translation toward the next.
	
	const float DEGMUL = pi<float>()/180;

	//extrinsic:
        mat4 precalcthis = 
	rotate(DEGMUL*b->basisRot.z,vec3(0,0,1)) *     //z third
	rotate(DEGMUL*b->basisRot.y,vec3(0,1,0)) *     //y second
	rotate(DEGMUL*b->basisRot.x,vec3(1,0,0));      //x first
	mat4 eulerBasis = accumR * precalcthis;

	// Include animation
	vec4 tz,ty,tx;
	tz = precalcthis * vec4(0,0,1,1);
	ty = precalcthis * vec4(0,1,0,1);
	tz = precalcthis * vec4(1,0,0,1);
	vec3 tz3, ty3, tx3;
	tz3 = vec3(tz.x,tz.y,tz.z);
	ty3 = vec3(ty.x,ty.y,ty.z);
	tx3 = vec3(tx.x,tx.y,tx.z);

	mat4 tweak = 

	rotate(DEGMUL*b->rotation.z,tz3) *     //z third
	rotate(DEGMUL*b->rotation.y,ty3) *     //y second
	rotate(DEGMUL*b->rotation.x,tz3) * mat4(1);      //x first

	mat4 myR = accumR * tweak;
	eulerBasis = tweak * eulerBasis;

	vec3 cpos = b->length*b->boneDir;
	mat4 nextOrigin = accumT * myR * translate(mat4(1.0), cpos);
	//mat4 nextOrigin = accumT * translate(mat4(1.0), cpos);  //test without articulation

	mat4 meshPoleRot(1.0);
	float latr=acos(b->boneDir.y);
	float lonr=atan(b->boneDir.x/b->boneDir.z); //Pole tips towards high noon

 	 //tip calls for the pole
	 mat4 tip = rotate(latr, vec3(1,0,0));
	 mat4 spin = rotate(lonr, vec3(0,1,0));
	meshPoleRot = myR * spin*tip * scale(mat4(),vec3(0.1,b->length,0.1));

 	//now draw the bone
	glUniform3f(glGetUniformLocation(m_program->m_program,"ucol"),
				0.8, 0.8, 0.8);
	m_program->setModelMatrix(accumT*meshPoleRot);
//	m_program->setModelMatrix(accumT);
	placeholderbone->draw();


	//Draw the bone's Tait-Bryan basis.
	//

 	mat4 myBasis = accumT*eulerBasis * scale(mat4(),vec3(0.1,0.1,0.1));			//Draw the axes back at the joint
	
	glUniform3f(glGetUniformLocation(m_program->m_program,"ucol"),
				1 , 0, 0);
	m_program->setModelMatrix(myBasis*rotate(0.5f* pi<float>() , vec3(0,0,1))) ;
	placeholderbone->draw();

	glUniform3f(glGetUniformLocation(m_program->m_program,"ucol"),
				0 , 1, 0);
	m_program->setModelMatrix(myBasis);
	placeholderbone->draw();

	glUniform3f(glGetUniformLocation(m_program->m_program,"ucol"),
				0 , 0, 1);
	m_program->setModelMatrix(myBasis*rotate(0.5f* pi<float>() , vec3(1,0,0))) ;
	placeholderbone->draw();



	for (bone * child : b->children) renderBone(nextOrigin, myR, child, placeholderbone);	
	

}


// Helper method for retreiving and trimming the next line in a file.
// You should not need to modify this method.
namespace {
	string nextLineTrimmed(istream &file) {
		// Pull out line from file
		string line;
		getline(file, line);
		// Remove leading and trailing whitespace and comments
		size_t i = line.find_first_not_of(" \t\r\n");
		if (i != string::npos) {
			if (line[i] != '#') {
				return line.substr(i, line.find_last_not_of(" \t\r\n") - i + 1);
			}
		}
		return "";
	}
}



//*** after reading in a skeleton, every bone will have a name
//*** this function allows you to find which bone has a particular
//*** name
int Skeleton::findBone(string name) {
	for (size_t i = 0; i < m_bones.size(); i++)
		if (m_bones[i].name == name)
			return i;
	return -1;
}


//*** read an ASF file
void Skeleton::readASF(string filename) {

	ifstream file(filename);

	if (!file.is_open()) {
		cerr << "Failed to open file " <<  filename << endl;
		throw runtime_error("Error :: could not open file.");
	}

	cout << "Reading file" << filename << endl;

	// good() means that failbit, badbit and eofbit are all not set
	while (file.good()) {

		// Pull out line from file
		string line = nextLineTrimmed(file);

		// Check if it is a comment or just empty
		if (line.empty() || line[0] == '#')
			continue;
		else if (line[0] == ':') {
			// Line starts with a ':' character so it must be a header
			readHeading(line, file);
		} else {
			// Would normally error here, but becuase we don't parse
			// every header entirely we will leave this blank.
		}
	}

	cout << "Completed reading skeleton file" << endl;
}


//*** read a heading line (one that starts with a colon ":")
void Skeleton::readHeading(string headerline, ifstream &file) {

	string head;
	istringstream lineStream(headerline);
	lineStream >> head; // get the first token from the stream

	// remove the ':' from the header name
	if (head[0] == ':')
		head = head.substr(1);

	if (lineStream.fail() || head.empty()) {
		cerr << "Could not get heading name from\"" << headerline << "\", all is lost" << endl;
		throw runtime_error("Error :: could not parse .asf file.");
	}

	if (head == "version") {
		//version string - must be 1.10
		string version;
		lineStream >> version;
		if (lineStream.fail() || version != "1.10") {
			cerr << "Invalid version: \"" << version << "\" must be 1.10" << endl;
			throw runtime_error("Error :: invalid .asf version.");
		}
	}
	else if (head == "name") {
		// This allows the skeleton to be called something
		// other than the file name. We don't actually care
		// what the name is, so can ignore this whole section
	}
	else if (head == "documentation") {
		// Documentation section has no meaningful information
		// only of use if you want to copy the file. So we skip it
	}
	else if (head == "units") {
		// Has factors for the units to be able to model the
		// real person, these must be parsed correctly. Only
		// really need to check if deg or rad, but that is 
		// not needed for this assignment.

		// We are going to assume that the units:length feild
		// is 0.45, and that the angles are in degrees
	}
	else if (head == "root") {
		// Read in information about root. Let's just assume
		// it'll be at the origin for this assignment.
	}
	else if (head == "bonedata") {
		// Read in each bone until we get to the
		// end of the file or a new header
		string line = nextLineTrimmed(file);
		while (file.good() && !line.empty()) {
			if (line[0] == ':') {
				// finished our reading of bones
				// read next header and return
				return readHeading(line, file);
			}
			else if (line == "begin") {
				// Read the bone data
				readBone(file);
			}
			else {
				cerr << "Expected 'begin' in bone data, found \"" << line << "\"";
				throw runtime_error("Error :: could not parse .asf file.");
			}
			line = nextLineTrimmed(file);
		}
	}
	else if (head == "hierarchy") {
		// Description of how the bones fit together
		// Read in each line until we get to the
		// end of the file or a new header
		string line = nextLineTrimmed(file);
		while (file.good() && !line.empty()) {
			if (line[0] == ':') {
				// finished our reading of bones
				// read next header and return
				return readHeading(line, file);
			}
			else if (line == "begin") {
				// Read the entire hierarchy
				readHierarchy(file);
			}
			else {
				cerr << "Expected 'begin' in hierarchy, found \"" << line << "\"";
				throw runtime_error("Error :: could not parse .asf file.");
			}
			line = nextLineTrimmed(file);
		}
	}
	else {
		// Would normally error here, but becuase we don't parse
		// every header entirely we will leave this blank.
	}

}


//*** read all the data related to a single bone and put it in the
//*** bone data structure (see skeleton.hpp for the data structure)
void Skeleton::readBone(ifstream &file) {
	// Create the bone to add the data to
	bone b;
	printf("bone!\n");

	string line = nextLineTrimmed(file);
	while (file.good()) {
		if (line == "end") {
			// End of the data for this bone
			// Push the bone into the vector
			m_bones.push_back(b);

			return;
		}
		else {
			
			string head;
			istringstream lineStream(line);
			lineStream >> head; // Get the first token

			if (head == "name") {
				// Name of the bone
				lineStream >> b.name;
				bonemap[b.name]=&b;
			}
			else if (head == "direction") {
				// Direction of the bone
				lineStream >> b.boneDir.x >> b.boneDir.y >> b.boneDir.z;
				b.boneDir = normalize(b.boneDir); // Normalize here for consistency
			}
			else if (head == "length") {
				// Length of the bone
				float length;
				lineStream >> length;
				length *= (1.0/0.45);  // scale by 1/0.45 to get actual measurements
				length *= 0.0254;      // convert from inches to meters
				b.length = length;
			}
			else if (head == "dof") {
				// Degrees of Freedom of the joint (rotation)
				while (lineStream.good()) {
					string dofString;
					lineStream >> dofString;
					if (!dofString.empty()) {
						// Parse each dof string
						if      (dofString == "rx") b.freedom |= dof_rx;
						else if (dofString == "ry") b.freedom |= dof_ry;
						else if (dofString == "rz") b.freedom |= dof_rz;
						else throw runtime_error("Error :: .asf file has invalid dof parameters.");
					}
				}
			}
			else if (head == "axis") {
				// Basis rotations 
				lineStream >> b.basisRot.x >> b.basisRot.y >> b.basisRot.z;
			}
			else if (head == "limits") {
				// Limits for each of the DOF
				// Assumes dof has been read first
				// You can optionally fill this method out
			}

			// Because we've tried to parse numerical values
			// check if we've failed at any point
			if (lineStream.fail()) {
				cerr << "Unable to parse \"" << line << "\"";
				throw runtime_error("Error :: could not parse .asf file.");
			}
		}

		// Get the next line
		line = nextLineTrimmed(file);
	}

	cerr << "Expected end in bonedata, found \"" << line << "\"";
	throw runtime_error("Error :: could not parse .asf file.");
}


//*** after you have read in all of the bones, you then
//*** need to connect them up into the hierarchy specified
//*** in the ASF file

void Skeleton::readHierarchy(ifstream &file) {
	string line = nextLineTrimmed(file);
	while (file.good()) {
		if (line == "end") {
			// End of hierarchy
			return;
		}
		else if (!line.empty()) {
			// Read the parent node
			string parentName;
			istringstream lineStream(line);
			lineStream >> parentName;

			// Find the parent bone and have a pointer to it
			int parentIndex = findBone(parentName);

			if (parentIndex < 0) {
				cerr << "Expected a valid parent bone name, found \"" << parentName << "\"" << endl;
				throw runtime_error("Error :: could not parse .asf file.");
			}

			//Read the connections
			string childName;
			lineStream >> childName;
			while (!lineStream.fail() && !childName.empty()) {

				int childIndex = findBone(childName);

				if (childIndex < 0) {
					cerr << "Expected a valid child bone name, found \"" << childName << "\"" << endl;
					throw runtime_error("Error :: could not parse .asf file.");
				}

				// Set a POINTER to the child to be recorded in the parents
				m_bones[parentIndex].children.push_back(&m_bones[childIndex]);
				
				// Get the next child
				lineStream >> childName;
			}
		}
		line = nextLineTrimmed(file);
	}
	cerr << "Expected end in bonedata, found \"" << line << "\"";
	throw runtime_error("Error :: could not parse .asf file.");
}



//*** For both COMP308 and CGRA350 you need to write the parser
//*** for an AMC file yourself. This can be based on the above
//*** code for the ASF file.
//-------------------------------------------------------------
// [Assignment 2] :
// Complete the following method to load data from an *.amc file
//-------------------------------------------------------------
void Skeleton::readAMC(string filename) {
	// YOUR CODE GOES HERE
	// ...

}

void Skeleton::applyFrame(std::vector<frame> & clip, float pos){

	//breakpoint here	
	printf("frame two:");
	
	for (auto const& x : clip[0]) {
		std::cout << x.first;  // string (key)

		std::cout << "Xrotation " << bonemap[x.first] << std::endl;
		//	<< ':' 
		//	<< x.second // string's value 
		//	<< std::endl ;
	}	

	unsigned int maxFrame = clip.size() - 1;

	unsigned int getFrame = glm::min( (unsigned int)(clip.size()-1), (unsigned int)(clip.size()*pos));

	printf ("getting frame %d:\n" ,getFrame);

	frame *k = &clip[getFrame];
	
	
	{
		for (auto const & e : *k){
			printf("getting bone %s \n" , e.first);
			
			//bone * fb = bonemap[e.first];
			bone * fb = &m_bones[findBone(e.first)];
			int fdm = fb -> freedom;
			//do some dof logic
			//fb->rotation = k.second;
			unsigned int nox=1, noy =1;
		 	if (fb->freedom > 3){
			fb->rotation.x=e.second[0];    
				nox=0;
			}
			if (fb->freedom > 0 && fb->freedom % 4 > 1){
			fb->rotation.y=e.second[1-nox];
				noy=0;
			}
			if (fb->freedom % 2 > 0){
			fb->rotation.z=e.second[2-nox-noy];
			}
				
		}
	}
}
// YOUR CODE GOES HERE
// ...
