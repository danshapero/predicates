#include <predicates.hpp>
#include <cassert>

int main()
{
    /**
     * This test was reported by github user mlivesu. The following four points
     * are coplanar but due to a bug in how the `splitter` variable was created
     * the 3D orientation predicate was giving an incorrect answer.
     */
    double x0[] = {7.878286361694336, -21.723194122314453, -13.910694122314453};
    double x1[] = {7.827281951904297, -21.42486572265625, -13.61236572265625};
    double x2[] = {7.860530853271484, -21.5969181060791, -13.784418106079102};
    double x3[] = {7.077847957611084, -21.82772445678711, -14.01522445678711};

    assert(predicates::orient3d(x0, x1, x2, x3) == 0.0);
    assert(predicates::orient3d(x2, x3, x0, x1) == 0.0);
}
