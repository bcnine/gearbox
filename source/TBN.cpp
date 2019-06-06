#include "TBN.h"
#include "Vector.h"

#include <iostream>

using namespace std;

namespace gbox
{

void
generateTangentVectors(ElementModel &model,
                       unsigned int positionidx,
                       unsigned int normalidx,
                       unsigned int textureidx,
                       unsigned int tangentidx)
{
	Vec3d *tan1 = new Vec3d[model.vertexCount()*2];
	Vec3d *tan2 = tan1 + model.vertexCount();

	for (unsigned int prim = 0; prim < model.primitiveCount(); ++prim)
	{
		if (model.primitiveType(prim) != GL_TRIANGLES)
			continue;

        for (unsigned int tri = 0; tri < model.primitiveTriCount(prim); ++tri)
		{
			Vec3d pos1, pos2, pos3;
			Vec2d tex1, tex2, tex3;
			unsigned int i1, i2, i3;
			model.primitiveTriElements(prim, tri, i1, i2, i3);
			model.attribute(prim, i1, positionidx, pos1[0], pos1[1], pos1[2]);
			model.attribute(prim, i2, positionidx, pos2[0], pos2[1], pos2[2]);
			model.attribute(prim, i3, positionidx, pos3[0], pos3[1], pos3[2]);
			model.attribute(prim, i1, textureidx, tex1[0], tex1[1]);
			model.attribute(prim, i2, textureidx, tex2[0], tex2[1]);
			model.attribute(prim, i3, textureidx, tex3[0], tex3[1]);

            double x1 = pos2.x() - pos1.x();
            double x2 = pos3.x() - pos1.x();
            double y1 = pos2.y() - pos1.y();
            double y2 = pos3.y() - pos1.y();
            double z1 = pos2.z() - pos1.z();
            double z2 = pos3.z() - pos1.z();
            double s1 = tex2.x() - tex1.x();
            double s2 = tex3.x() - tex1.x();
            double t1 = tex2.y() - tex1.y();
            double t2 = tex3.y() - tex1.y();

			double r = 1.0 / (s1*t2 - s2*t1);
			Vec3d s((t2*x1 - t1*x2)*r, (t2*y1 - t1*y2)*r, (t2*z1 - t1*z2)*r);
			Vec3d t((s1*x2 - s2*x1)*r, (s1*y2 - s2*y1)*r, (s1*z2 - s2*z1)*r);

			unsigned int offset = model.primitiveVertexOffset(prim);
			tan1[offset+i1] += s;
			tan1[offset+i2] += s;
			tan1[offset+i3] += s;
			tan2[offset+i1] += t;
			tan2[offset+i2] += t;
			tan2[offset+i3] += t;
		}
	}

	for (unsigned int i = 0; i < model.vertexCount(); ++i)
	{
		Vec3d n, t(tan1[i]);
        model.directAttribute(i, normalidx, n.x(), n.y(), n.z());
		Vec3d tangent(((t - n*(n * t))).normalize());
		double w = (((n % t) * tan2[i]) < 0) ? -1 : 1;

        model.setDirectAttribute(i, tangentidx, tangent.x(), tangent.y(), tangent.z(), w);
	}

	//cout << "----" << endl;
	//cout << "vertices" << endl;
	for (unsigned int i = 0; i < model.vertexCount(); ++i)
	{
		double x, y, z;
		model.directAttribute(i, positionidx, x, y, z); 
		//cout << x << " " << y << " " << z << endl;
	}
	//cout << "tangents" << endl;
	for (unsigned int i = 0; i < model.vertexCount(); ++i)
	{
		double x, y, z, w;
		model.directAttribute(i, tangentidx, x, y, z, w); 
		//cout << x << " " << y << " " << z << " " << w << endl;
	}

	delete [] tan1;
}

};
