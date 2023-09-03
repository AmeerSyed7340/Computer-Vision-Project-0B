#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;


class Image {
public:
	int numRows;
	int numCols;
	int minVal;
	int maxVal;
	int thrVal;

	Image(int numRows, int numCols, int minVal, int maxVal, int thrVal) {
		this->numRows = numRows;
		this->numCols = numCols;
		this->minVal = minVal;
		this->maxVal = maxVal;
		this->thrVal = thrVal;
	}//constructor

	void Processing(fstream& inFile, ofstream& outFile1, ofstream& outFile2, int thrVal) {
		//step 0
		int pixelVal;
		int count = 0;

		//step 1
		string line;
		getline(inFile, line);

		while (inFile >> pixelVal) {
			if (pixelVal >= thrVal) {
				outFile1 << 1 << " ";
				outFile2 << pixelVal << " ";
			}
			else {
				outFile1 << 0 << " ";
				outFile2 << 0 << " ";
			}
			count++;
			if (count == numCols) {
				outFile1 << endl;
				outFile2 << endl;
				count = 0;
			}
		}
	}//Processing
};
int main(int argc, const char* argv[]) {
	fstream inFile;
	ofstream outFile1;
	ofstream outFile2;

	//make sure user inputs all files
	if (argc != 4) {
		cout << "Need one inFile and two outFiles";
	}
	else {
		inFile.open(argv[1]);
		outFile1.open(argv[2]);
		outFile2.open(argv[3]);
	}
	//Local vars to pass into img object
	int numRows;
	int numCols;
	int minVal;
	int maxVal;
	int thrVal;

	//Read the first line only and save it into string line
	string line;
	getline(inFile, line);
	
	istringstream iss(line);
	iss >> numRows >> numCols >> minVal >> maxVal;

	//take user input for threshold value
	cout << "Please enter a threshold value:" << endl;
	cin >> thrVal;

	Image *img = new Image(numRows, numCols, minVal, maxVal, thrVal);

	//add the row and col headers on top
	outFile1 << numRows << " " << numCols << " " << minVal << " " << maxVal << endl;
	outFile2 << numRows << " " << numCols << " " << minVal << " " << maxVal << endl;

	img->Processing(inFile, outFile1, outFile2, thrVal);

	inFile.close();
	outFile1.close();
	outFile2.close();
}