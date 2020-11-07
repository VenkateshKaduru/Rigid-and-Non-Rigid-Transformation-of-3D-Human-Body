# Rigid and Non-rigid Transformation of two 3D Human full-body scans.

## **Introduction**

3D Alignment/Transformation of meshes is one of the important task in statistical shape model fitting pipeline. [Procrustes analysis](https://en.wikipedia.org/wiki/Procrustes_analysis) is the most well-known method for aligning the 3d objects. [Rigid transformation](https://en.wikipedia.org/wiki/Rigid_transformation) includes translation and rotation. Non-rigid alignment is also called as [similarity transformation](https://en.wikipedia.org/wiki/Similarity_transformation) that includes translation, rotation, and uniform scaling. In this project we are transforming a target mesh rigidly and non-rigidly to a reference mesh. This means that, by displacing/bring/adjust the target mesh's orientation and shape properties in order to macth the reference mesh in 3D space.

## Feature
- VTK made this work easy. It is providing three different transformations Rigid, Similarity, Affine as a member functions. You will find the details [here](https://vtk.org/doc/nightly/html/classvtkLandmarkTransform.html#details). We can simply set the Member Function, for example, `SetModeToRigidBody()` or `SetModeToSimilarity()` to get the required transformation.

## Note
- The member functions required landmark points to compute the transformation. Therefore, you need reference and target meshes landmark points. These landmark points you can take by using meshlab tool.

## Requirments
- VTK 8.2.0
- CMake
- MeshLab
- Visual Studio 2017

## Building
1. Install VTK
1. Build the main.cpp file by using CMake
1. Provid reference and target meshes file paths as input in the code
1.  To save the aligned output, provid output file name and path in the code
1. Provide the reference and target meshes landmark points in the code
1. Done, you got the aligned output :-)




  
