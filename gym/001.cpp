// https://stackoverflow.com/questions/10878611/why-is-it-not-allowed-to-specialize-a-member-function-template-within-a-class


#include <iostream>

class surfaceMesh 
{
    public:
        // Uncomment for Version 0 and 1
        class AREA_AVERAGE {};
        class ANGLE_AVERAGE {};  

        template<class Average>
        void vertexNormals() {}

        // Uncomment: Version 0
        //template<>
        //void vertexNormals<AREA_AVERAGE> ()
        //{
            //std::cout << "AREA_AVERAGE" << std::endl;
        //}

        //template<>
        //void vertexNormals<ANGLE_AVERAGE> ()
        //{
            //std::cout << "ANGLE_AVERAGE" << std::endl;
        //}


};
template<>
void surfaceMesh::vertexNormals<surfaceMesh::AREA_AVERAGE> ()
{
    std::cout << "AREA_AVERAGE" << std::endl;
};

template<>
void surfaceMesh::vertexNormals<surfaceMesh::ANGLE_AVERAGE> ()
{
    std::cout << "ANGLE_AVERAGE" << std::endl;
};


int main()
{
    surfaceMesh m;

    m.vertexNormals<surfaceMesh::AREA_AVERAGE>();
    m.vertexNormals<surfaceMesh::ANGLE_AVERAGE>();

    return 0;
}
