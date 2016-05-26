#include "npywriter.h"

namespace PathTrace {

NPYWriter::NPYWriter(const std::string& filename)
{
	out.open(filename.c_str(), std::ofstream::out | std::ofstream::binary);
}

NPYWriter::~NPYWriter()
{
	out.close();
}

void NPYWriter::writeHeader(std::vector<uint> dim)
{
    out.write("\x93NUMPY", 6);
    char version[2] = {0x01, 0x00};
    out.write(version, 2);

    std::string header = "{'descr':'f','fortran_order':False, 'shape': (";
    uint i;
	for (i = 0; i < dim.size() - 1; i++) {	
		header += std::to_string(dim[i]) + ",";
	}
	header += std::to_string(dim[i]) + ")}";

    short size = header.size();
    out.write((char*) &size, 2);
    out.write(header.c_str(), header.size());
}

void NPYWriter::write(std::vector<float> data)
{
	out.write((char*) data.data(), sizeof(float) * data.size());
}

}