
#include <iostream>
#include <string>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include"build/Reader.h"

int main(int argc, char* argv[])
{
	const char* filePathReferenceData = "D:/HP_Laptop/Thesis/Reader/parameters.vtk";
	const char* filePathTargetData = "D:/HP_Laptop/Thesis/Reader/Venkatesh_Mesh.vtk";
	//const char* filePathAlignedOutput = "C:/VTK/Reader/AlignedOutput.vtk";

	Reader r;
	vtkSmartPointer<vtkPolyData> reference;
	reference = r.loadVTKPolyData(filePathReferenceData);

	vtkSmartPointer<vtkPolyData> target;
	target = r.loadVTKPolyData(filePathTargetData);

	r.visualize(reference, target);

	return EXIT_SUCCESS;
}

