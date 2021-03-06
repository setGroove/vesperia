#ifndef STRUCTUREDHEXMESH_H_INCLUDED
#define STRUCTUREDHEXMESH_H_INCLUDED

//#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "../maths/vectors.h"

class structuredHexMesh : public vec3
{
    protected:

	std::string m_name;
    unsigned m_H;
    unsigned m_W;
    unsigned m_L;
    unsigned m_HW;
    unsigned m_id;
    unsigned m_Vertex_Population;
    unsigned m_Face_Population;
    unsigned m_Volume_Population;

    float m_Total_Volume;
    float m_cell_Volume;

    public:

    std::vector<vec3> Mesh;
    std::vector<unsigned char> Boundary_Cell;
    std::vector<vec3> Cell_Centroids;
    std::vector<bool> Cell_Divided; //TODO CELL_DIVIDED COULD BE ASIMILATED INSIDE BOUNDARY_CELL USING LEFT BIT
    std::vector<vec3> Face_UNormals;
    std::vector<vec3> Face_Centroids;

    std::vector<float> u;
    std::vector<float> r;
    std::vector<float> T;
    std::vector<float> p;

    vec3* Vertex[8];
    vec3* Edge_i[12]; //        int id_vert[] = {0,2, 1,3, 2,5, 1,6, 5,7, 4,6, 7,0, 4,3, 0,5, 4,1, 2,7, 6,3 }
    vec3* Edge_j[12];
    vec3* Tris[3*2*6];
    vec3* Quad[4*6];

    int Total_Cell_Divided;

    public:

    structuredHexMesh(std::string name);
    structuredHexMesh(std::string name, unsigned nel_TSx, unsigned nel_TSy, unsigned nel_TSz);
    ~structuredHexMesh();

    protected:

    structuredHexMesh(std::string name, unsigned vertex_Population);
//     structuredHexMesh(const unsigned H, const unsigned W, const unsigned L, const unsigned count_mesh, const unsigned  count_faces, const unsigned count_volumes);

    public:

    void DisplaceMesh(const vec3& offset);              //Rigid body 3Ddisplace of the mesh
    void RotateXMesh(const float &alphax);              //Rigid body X-rotation of the mesh
    void RotateYMesh(const float &alphay);              //Rigid body Y-rotation of the mesh
    void RotateZMesh(const float &alphaz);              //Rigid body Z-rotation of the mesh

    void loadCellEdges();        //Pass global *Mesh.Vertex -> Vertex & Edge_ij

    float AreaC3(const vec3& p1, const vec3& p2, const vec3& p3);
//    float AreaC4(const vec3& v0, const vec3& v1, const vec3& v2, const vec3& v3);
    vec3 CenterC3(const vec3& p1, const vec3& p2, const vec3& p3);
    vec3 CenterC4(const vec3& p1, const vec3& p2, const vec3& p3, const vec3& p4);
    vec3 CenterT4(const vec3& v0, const vec3& v1, const vec3& v2, const vec3& v3);
    float VolumeT4(const vec3& v0, const vec3& v1, const vec3& v2, const vec3& v3);
    void CenterC8();

    void setOctreeLevel1(vec3 Qt[], int Divisions);
    void setOctreeLevel2(vec3 Qt[], int Divisions);

    void SweepFace(const vec3* Surface, const int& nel_X, const int& nel_Z, const int& nel_Sweep, const float& delta_Sweep, const vec3& origin_Sweep);

    virtual void loadVertexId(const unsigned& id);
    
	bool vertexSearchCell(const vec3& point);
    
	void Log() const;

	const void LogMembers() const;
    void Log_Cell();
    void Log_Cells() const;
    unsigned Log_Cells_Max() const;
    unsigned Log_Verts() const;

//	void WriteMesh(std::string nameFile);
	void WriteMesh(std::ofstream *meshFileOF, std::string nameFile, int level);
	void drawMesh(float alpha0);
	private:
	void AllocateMesh();

};

#endif // STRUCTUREDHEXMESH_H_INCLUDED
