#include "loadObj.h"

void getPointIdx(std::string &buffer, int&v, int&uv, int &nm);

std::string fillPath(const char* parentName, const char* filename) {
	std::string fullpath(parentName);
	size_t pathpt = fullpath.rfind('/');
	std::string fpath = fullpath.substr(0, pathpt + 1);
	fpath += filename;
	return fpath;
}

void SubMesh::draw()
{
}

SubMesh::SubMesh() {

	ptBuffer = 0;
	vNum = 0;
	uvBuffer = 0;
	nmBuffer = 0;
}

SubMesh::~SubMesh()
{
	if (ptBuffer != 0) {
		free(ptBuffer);
	}
	if (uvBuffer != 0) {
		free(uvBuffer);
	}
	if (nmBuffer != 0) {
		free(nmBuffer);
	}
}

void Object::draw()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnable(GL_NORMALIZE);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_COLOR_MATERIAL);
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRotated(angle,1.0,0,0);
	for (std::list<SubMesh*>::iterator i = children.begin(); i != children.end(); i++) {
		Material mt = material_map[(*i)->mtName];
		SetMaterial(GL_FRONT_AND_BACK, GL_AMBIENT, mt.ka);
		SetMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE, mt.kd);
		SetMaterial(GL_FRONT_AND_BACK, GL_SPECULAR, mt.ks);
		glBindTexture(GL_TEXTURE_2D, mt.kd_texid);
		glVertexPointer(3, GL_FLOAT, 0, (*i)->ptBuffer);
		glTexCoordPointer(2, GL_FLOAT, 0, (*i)->uvBuffer);
		glNormalPointer(GL_FLOAT, 0, (*i)->nmBuffer);
		glDrawArrays(GL_TRIANGLES, 0, (*i)->vNum);
	}
	glPopMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_NORMALIZE);
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void Object::parsePolygon(std::ifstream & ifs, std::string &name)
{
	int totalFace = countFaceNumber(ifs);
	SubMesh* pMesh = new SubMesh;
	std::string curline;
	pMesh->mtName = name;
	pMesh->fcNum = totalFace;
	pMesh->vNum = totalFace * 3;
	pMesh->ptBuffer = (Point*)malloc(sizeof(Point)*pMesh->vNum);
	pMesh->uvBuffer = (UVPoint*)malloc(sizeof(UVPoint)*pMesh->vNum);
	pMesh->nmBuffer = (NMPoint*)malloc(sizeof(NMPoint)*pMesh->vNum);
	int cur_pt = 0;
	int cur_fc = 0;
	while (std::getline(ifs, curline)) {
		std::stringstream strstm(curline);
		std::string head;
		strstm >> head;
		if (head == "f") {
			std::string pt;
			while (!strstm.eof()) {
				if (!(strstm >> pt)) {
					break;
				}
				int v, uv, nm;
				getPointIdx(pt, v, uv, nm);
				memcpy(pMesh->ptBuffer[cur_pt], ptBuffer[v - 1], sizeof(Point));
				memcpy(pMesh->uvBuffer[cur_pt], uvBuffer[uv - 1], sizeof(UVPoint));
				memcpy(pMesh->nmBuffer[cur_pt], nmBuffer[nm - 1], sizeof(NMPoint));
				cur_pt = cur_pt + 1;
			}
			cur_fc = cur_fc + 1;
			if (cur_fc == totalFace) {
				break;
			}
		}
		if (head == "g") {
			std::string fcname;
			strstm >> fcname;
			pMesh->fcName = fcname;
		}
	}
	children.push_back(pMesh);
}

void getPointIdx(std::string & buffer, int & v, int & uv, int & nm)
{
	std::string vbuf;
	std::string uvbuf;
	std::string nmbuf;
	v = -1;
	uv = -1;
	nm = -1;
	int idx = 0;
	for (int i = 0; i < buffer.size(); i++) {
		if (buffer[i] == '/') {
			idx++;
			continue;
		}
		switch (idx)
		{
		case 0:
			vbuf += buffer[i];
			break;
		case 1:
			uvbuf += buffer[i];
			break;
		case 2:
			nmbuf += buffer[i];
			break;
		default:
			break;
		}
	}
	v = atoi(vbuf.c_str());
	uv = atoi(uvbuf.c_str());
	nm = atoi(nmbuf.c_str());
}

int Object::countFaceNumber(std::ifstream & ifs)
{
	std::streampos cur = ifs.tellg();
	std::string curline;
	int totalFace = 0;
	while (std::getline(ifs, curline)) {
		if (curline[0] == 'f') {
			totalFace++;
		}
		if (curline[0] != '#'&&curline[0] != 'f'&&curline[0] != 'g' && curline[0] != 's') {
			break;
		}
	}
	ifs.clear();
	ifs.seekg(cur);
	return totalFace;
}

void Object::countNumber(std::ifstream& ifs)
{
	std::streampos cur = ifs.tellg();
	std::string curline;
	while (std::getline(ifs, curline)) {
		if (curline[0] == 'v') {
			if (curline[1] == 't') {
				vtNum++;
			}
			else if (curline[1] == 'n') {
				vnNum++;
			}
			else {
				vNum++;
			}
		}
	}
	ifs.clear();
	ifs.seekg(cur);
}

void Object::loadMtl(const char * filename)
{
	std::ifstream ifs(filename);
	if (!ifs) {
		std::cout << "找不到材质文件:" << filename << '\n';
		std::cout << "任意键退出\n";
		std::cin.get();
		exit(0);
	}
	std::string curline;
	while (std::getline(ifs, curline)) {
		std::stringstream strstm(curline);
		std::string head;
		strstm >> head;
		if (head == "newmtl") {
			std::string name;
			strstm >> name;
			while (std::getline(ifs, curline)) {
				if (curline == "") {
					break;
				}
				std::stringstream curstm(curline);
				curstm >> head;
				if (head == "illum") {
					curstm >> material_map[name].illum;
				}
				if (head == "Kd") {
					curstm >> material_map[name].kd.r;
					curstm >> material_map[name].kd.g;
					curstm >> material_map[name].kd.b;
				}
				if (head == "Ka") {
					curstm >> material_map[name].ka.r;
					curstm >> material_map[name].ka.g;
					curstm >> material_map[name].ka.b;
				}
				if (head == "Ks") {
					curstm >> material_map[name].ks.r;
					curstm >> material_map[name].ks.g;
					curstm >> material_map[name].ks.b;
				}
				if (head == "Ke") {
					curstm >> material_map[name].ke.r;
					curstm >> material_map[name].ke.g;
					curstm >> material_map[name].ke.b;
				}
				if (head == "Ns") {
					curstm >> material_map[name].ns;
				}
				if (head == "map_Kd") {
					std::string texname;
					curstm >> texname;
					std::string fpath = fillPath(filename, texname.c_str());
					if (texname[texname.size() - 1] == 'p') {
						loadTexture(fpath.c_str(), material_map[name].kd_texid);
					}
					/*
					else if (!loadTexture(fpath.c_str(), material_map[name].kd_texid, GL_BGRA, GL_RGBA)) {
						std::cout << "无法加载纹理:" << fpath << '\n';
					}
					*/
				}
			}
		}
	}
}

void Object::loadFromObj(const char * filename)
{
	std::ifstream ifs(filename);
	if (!ifs) {
		std::cout << "找不到模型文件:" << filename << '\n';
		std::cout << "任意键退出\n";
		std::cin.get();
		exit(0);
	}
	countNumber(ifs);
	std::string curline;
	ptBuffer = new Point[vNum];
	nmBuffer = new NMPoint[vnNum];
	uvBuffer = new UVPoint[vtNum];
	GLuint cur_vp = 0;
	GLuint cur_vnp = 0;
	GLuint cur_vtp = 0;
	while (std::getline(ifs, curline)) {
		std::stringstream strstm(curline);
		std::string head;
		strstm >> head;
		if (head == "mtllib") {
			std::string fname;
			strstm >> fname;
			std::string fpath = fillPath(filename, fname.c_str());
			loadMtl(fpath.c_str());
		}
		if (head == "v") {
			float x, y, z;
			strstm >> x >> y >> z;
			ptBuffer[cur_vp][0] = x;
			ptBuffer[cur_vp][1] = y;
			ptBuffer[cur_vp][2] = z;
			cur_vp++;
		}
		if (head == "vt") {
			float u, v;
			strstm >> u >> v;
			int ui = u;
			int vi = v;
			if (ui == 1)
				u = 1;
			else
				u -= ui;
			if (vi == 1)
				v = 1;
			else
				v -= vi;
			uvBuffer[cur_vtp][0] = u;
			uvBuffer[cur_vtp][1] = v;
			cur_vtp++;
		}
		if (head == "vn") {
			float x, y, z;
			strstm >> x >> y >> z;
			nmBuffer[cur_vnp][0] = x;
			nmBuffer[cur_vnp][1] = y;
			nmBuffer[cur_vnp][2] = z;
			cur_vnp++;
		}
		if (head == "usemtl") {
			std::string name;
			strstm >> name;
			parsePolygon(ifs, name);
		}
	}
}

/*
void Object::calcHeight()
{
	if (height == NULL)
	{
		GLuint num = sqrt(vNum);
		height = new GLfloat*[num];
		for (GLuint i = 0; i < num; i++)
		{
			height[i] = new GLfloat[num];
		}
		GLfloat last_x = -100.0f;
		GLfloat last_y = 100.0f;
		GLuint px = 0;
		GLuint py = num - 1;
		for (GLuint i = 0; i < vNum; i++)
		{
			GLfloat x = ptBuffer[i][0];
			GLfloat z = ptBuffer[i][1];
			GLfloat y = ptBuffer[i][2];
			if (x < last_x)
			{
				if (last_x > 0 && x < 0)
				{
					px = 0;
				}
				else 
				{
					px--;
				}
			}
			else if (x > last_x)
			{
				px++;
			}
			if (y < last_y)
			{
				py--;
			}
			else if(y > last_y)
			{ 
				py++;
			}
			height[py][px] = z;
			last_x = x;
			last_y = y;
		}
	}
}
*/

Object::Object() :vNum(0), vtNum(0), vnNum(0), angle(0), position(0.0, 0.0, 0.0) {
	ptBuffer = NULL;
	uvBuffer = NULL;
	nmBuffer = NULL;
}

Object::~Object()
{
	if (ptBuffer != NULL) {
		delete[] ptBuffer;
	}
	if (uvBuffer != NULL) {
		delete[] uvBuffer;
	}
	if (nmBuffer != NULL) {
		delete[] nmBuffer;
	}
	for (std::list<SubMesh*>::iterator i = children.begin(); i != children.end(); i++) {
		delete *i;
	}
	if (height != NULL) {
		GLuint num = sqrt(vNum);
		for (GLuint i = 0; i < num; i++)
		{
			delete[] height[i];
		}
		delete[] height;
	}
}
