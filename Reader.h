#pragma once
#include<iostream>
#include<vtkPolyData.h>

class Reader {

public:
	vtkSmartPointer<vtkPolyData> loadVTKPolyData(const std::string& filename);
	void visualize(vtkSmartPointer<vtkPolyData> reference, vtkSmartPointer<vtkPolyData> target);


};

