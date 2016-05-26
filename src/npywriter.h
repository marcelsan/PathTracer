#ifndef NPYWRITER_H
#define NPYWRITER_H

#include <fstream>
#include <vector>

namespace PathTrace {

class NPYWriter {
public:
	NPYWriter(const std::string& filename);
	~NPYWriter();

	void writeHeader(std::vector<uint> dim);
	void write(std::vector<float> data);

private:
	std::ofstream out;
};

}

#endif // NPYWRITER_H