#include"Reader.h"
#include <iostream>
#include <string>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkPolyDataReader.h>
#include<vtkTransform.h>
#include<vtkTransformFilter.h>
#include<vtkTransformPolyDataFilter.h>
#include <vtkPolyDataWriter.h>
#include<vtkCellArray.h>
#include<vtkPoints.h>
#include<vtkCenterOfMass.h>
#include<vtkLandmarkTransform.h>

vtkSmartPointer<vtkPolyData> Reader::loadVTKPolyData(const std::string& filename) {
	vtkPolyDataReader* reader = vtkPolyDataReader::New();
	reader->SetFileName(filename.c_str());
	reader->Update();
	vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
	polydata->ShallowCopy(reader->GetOutput());
	return polydata;
}

void Reader::visualize(vtkSmartPointer<vtkPolyData> reference,
	vtkSmartPointer<vtkPolyData> target)
{
	//Compute Sacle for target
	vtkSmartPointer<vtkTransform> transform =
		vtkSmartPointer<vtkTransform>::New();
	transform->Scale(1, 1, 1);

	vtkSmartPointer<vtkTransformFilter> transformFilter =
		vtkSmartPointer<vtkTransformFilter>::New();
	transformFilter->SetInputData(target);
	transformFilter->SetTransform(transform);
	transformFilter->Update();

	// Compute the center of mass but is it necessary!, No
	vtkSmartPointer<vtkCenterOfMass> centerOfMassFilter =
		vtkSmartPointer<vtkCenterOfMass>::New();
	centerOfMassFilter->SetInputConnection(transformFilter->GetOutputPort());
	centerOfMassFilter->SetUseScalarsAsWeights(false);
	centerOfMassFilter->Update();
	double center[3];
	centerOfMassFilter->GetCenter(center);

	std::cout << "Center of mass is " << center[0] << " " << center[1] << " " << center[2] << std::endl;
	//landmarks of reference

	vtkSmartPointer<vtkPoints> referenceLandmarkPoints;
	referenceLandmarkPoints = vtkSmartPointer<vtkPoints>::New();

	double sourcePoint1[3] = { -448.65, 874.4, -107.64 };//RH
	referenceLandmarkPoints->InsertNextPoint(sourcePoint1);
	double sourcePoint2[3] = { 1.3684, 1739.3, -55.428 };//Head
	referenceLandmarkPoints->InsertNextPoint(sourcePoint2);
	double sourcePoint3[3] = { 4.8332, 1670.3, -23.645 };//Nose
	referenceLandmarkPoints->InsertNextPoint(sourcePoint3);
	double sourcePoint4[3] = { 473.43, 868.37, -83.275 };//LH
	referenceLandmarkPoints->InsertNextPoint(sourcePoint4);
	double sourcePoint5[3] = { 249.52, 14.696, -21.97 };//LL
	referenceLandmarkPoints->InsertNextPoint(sourcePoint5);
	double sourcePoint6[3] = { -135.46, -2.1743, -11.631 };//RL
	referenceLandmarkPoints->InsertNextPoint(sourcePoint6);

	vtkSmartPointer<vtkPolyData> referenceLandmarks;
	referenceLandmarks = vtkSmartPointer<vtkPolyData>::New(),
		referenceLandmarks->SetPoints(referenceLandmarkPoints);

	//landmarks of target
	vtkSmartPointer<vtkPoints> targetLandmarkPoints;
	targetLandmarkPoints = vtkSmartPointer<vtkPoints>::New();

	//Target mesh landmarks
	//double targetPoint1[3] = { 0.324158, 0.036222, 0.861999 };//RH
	//targetLandmarkPoints->InsertNextPoint(targetPoint1);
	//double targetPoint2[3] = { -0.017049, 0.126695, 1.66482 };//Nose
	//targetLandmarkPoints->InsertNextPoint(targetPoint2);
	//double targetPoint3[3] = { -0.343462, 0.02914, 0.873912 };//LH
	//targetLandmarkPoints->InsertNextPoint(targetPoint3);
	//double targetPoint4[3] = { -0.150376, 0.113667, 0.017809 };//LL
	//targetLandmarkPoints->InsertNextPoint(targetPoint4);
	//double targetPoint5[3] = { 0.161419, 0.112857, 0.0101319 };//RL
	//targetLandmarkPoints->InsertNextPoint(targetPoint5);

	//Venkatesh_Mesh Landmarks
	double targetPoint1[3] = { -311.547, 821.352, -125.447 };//RH
	targetLandmarkPoints->InsertNextPoint(targetPoint1);
	double targetPoint2[3] = { -5.85831, 1757.58, -66.6923 };//Head
	targetLandmarkPoints->InsertNextPoint(targetPoint2);
	double targetPoint3[3] = { -8.14529, 1653.58, -37.2382 };//Nose
	targetLandmarkPoints->InsertNextPoint(targetPoint3);
	double targetPoint4[3] = { 374.749, 869.858, -111.114 };//LH
	targetLandmarkPoints->InsertNextPoint(targetPoint4);
	double targetPoint5[3] = { 218.286, 5.91288, -21.2012 };//LL
	targetLandmarkPoints->InsertNextPoint(targetPoint5);
	double targetPoint6[3] = { -108.34, 10.1799, -28.4926 };//RL
	targetLandmarkPoints->InsertNextPoint(targetPoint6);

	vtkSmartPointer<vtkPolyData> targetLandmarks;
	targetLandmarks = vtkSmartPointer<vtkPolyData>::New();
	targetLandmarks->SetPoints(targetLandmarkPoints);


	vtkSmartPointer<vtkLandmarkTransform> landmarktransform =
		vtkSmartPointer<vtkLandmarkTransform>::New();

	landmarktransform->SetSourceLandmarks(targetLandmarkPoints);
	landmarktransform->SetTargetLandmarks(referenceLandmarkPoints);
	landmarktransform->SetModeToSimilarity();
	landmarktransform->Update();

	vtkSmartPointer<vtkTransformPolyDataFilter> transformFilter1 =
		vtkSmartPointer<vtkTransformPolyDataFilter>::New();
	// without scale
	//transformFilter1->SetInputData(target);
	//with scale
	transformFilter1->SetInputConnection(transformFilter->GetOutputPort());

	transformFilter1->SetTransform(landmarktransform);
	transformFilter1->Update();

	// Display the transformation matrix that was computed
	vtkMatrix4x4* mat = landmarktransform->GetMatrix();
	std::cout << "Matrix: " << *mat << std::endl;

	vtkSmartPointer<vtkPolyData> alignedOutput;
	alignedOutput = vtkSmartPointer<vtkPolyData>::New();
	alignedOutput->DeepCopy(transformFilter1->GetOutput());

	vtkSmartPointer<vtkPolyDataWriter> writer =
		vtkSmartPointer<vtkPolyDataWriter>::New();
	writer->SetFileName("AlignedOutput.vtk");
	writer->SetInputData(alignedOutput);
	writer->Write();


	vtkSmartPointer<vtkPolyDataMapper> mapper1 =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper1->SetInputData(reference);

	vtkSmartPointer<vtkPolyDataMapper> mapper2 =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper2->SetInputData(alignedOutput);
	//mapper2->SetInputConnection(transformFilter1->GetOutputPort());


	vtkSmartPointer<vtkActor> actor1 =
		vtkSmartPointer<vtkActor>::New();
	actor1->SetMapper(mapper1);

	vtkSmartPointer<vtkActor> actor2 =
		vtkSmartPointer<vtkActor>::New();
	actor2->SetMapper(mapper2);


	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();

	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	renderer->AddActor(actor1);
	renderer->AddActor(actor2);
	renderer->SetBackground(0, 0, 0);
	renderWindow->Render();
	renderWindowInteractor->Start();
}

