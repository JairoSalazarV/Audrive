#include <iostream>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <ctime>

#define		_OK			1
#define		_ERROR		0
#define		_FAIL		2

using namespace std;

typedef struct structSettings
{
	string audioDuration;   //Seconds
	string sleepTime;       //Seconds       
	string outputPath;      //Path
}structSettings;

int readFileContain( const string &fileName, string* contain );
int readSettings( structSettings* settings );
int getdir( string dir, vector<string> &files );
double stringToDouble( string str );
int executeConsoleCommand( string command, string* result );
const vector<string> explode(const string& s, const char& c);
string getTimeStampFilename( const structSettings& settings );
string getNextTime( const structSettings& settings );


int main()
{
	//--------------------------------------
	//Get Settings
	//--------------------------------------
	structSettings settings;
	if( readSettings( &settings ) != _OK )
	{
		//cout << "[ERROR] Reading Settings" << endl;
		return _ERROR;
	}
	
	//--------------------------------------
	//Prepare Variables
	//--------------------------------------
	cout << "Hello Audrive!\n\n" << endl;
	
	cout << "audioDuration " << settings.audioDuration << endl;
	cout << "sleepTime " << settings.sleepTime << endl;
	cout << "outputPath " << settings.outputPath << endl << endl;
	
	int sleepTime = (int)stringToDouble( settings.sleepTime );
	string tmpString;
    string tmpCommand;
    string commandResult;

	while(true)
	{
		//Shows when will occurs next recording
		tmpString.clear();
		tmpString = getNextTime( settings );
		cout << "Next snapshot on " << tmpString << endl;
        //Obtains next outputFile
        tmpString.clear();
		tmpString = getTimeStampFilename( settings );
        //cout << "Output Filename: " << tmpString << endl;
		sleep( sleepTime );
        //Start a new audio recording
        tmpCommand.clear();
        tmpCommand.append("arecord --duration=");
        tmpCommand.append(settings.audioDuration);
        tmpCommand.append(" ");
        tmpCommand.append(tmpString);
        executeConsoleCommand( tmpCommand, &commandResult );
	    //cout << "commandResult: " << commandResult << endl;
	}

    return _OK;	
}

string getNextTime( const structSettings& settings )
{
	//Timestamp
	time_t now = time(0) + (int)stringToDouble(settings.sleepTime);
	tm *ltm = localtime(&now);
	//Filename based on time stamp
	string tmpName;
	tmpName.clear();
	if( ltm->tm_mday < 10 )tmpName.append("0");
	tmpName.append( std::to_string(ltm->tm_mday) );	
	tmpName.append( "_" );
	if( ltm->tm_mon < 10 )tmpName.append("0");
	tmpName.append( std::to_string( (1+ltm->tm_mon) ) );
	tmpName.append( "_" );
	tmpName.append( std::to_string( (1900+ltm->tm_year) ) );
	tmpName.append( "_" );
	if( ltm->tm_hour < 10 )tmpName.append("0");
	tmpName.append( std::to_string( (ltm->tm_hour) ) );
	tmpName.append( "_" );
	if( ltm->tm_min < 10 )tmpName.append("0");
	tmpName.append( std::to_string( (ltm->tm_min) ) );
	tmpName.append( "_" );
	if( ltm->tm_sec < 10 )tmpName.append("0");
	tmpName.append( std::to_string( (ltm->tm_sec) ) );
	//Finish
	return tmpName;
}

string getTimeStampFilename( const structSettings& settings )
{
	//Carpeta destino
	string outputFile;
	outputFile.append( settings.outputPath );
    //Nombre de archivo
    outputFile.append( getNextTime( settings ) );
    //Extensión de archivo de salida
    outputFile.append( ".wav" );
	//Return
	return outputFile;
}

const vector<string> explode(const string& s, const char& c)
{
	string buff{""};
	vector<string> v;
	
	for(auto n:s)
	{
		if(n != c) buff+=n; else
		if(n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if(buff != "") v.push_back(buff);
	
	return v;
}

int executeConsoleCommand( string command, string* result )
{
	//Execute Console Command
	int frameBodyLen = 1024;
	char bufferComm[frameBodyLen];
	result->clear();
	FILE* pipe = popen(command.c_str(), "r");
	try
	{
		while(!feof(pipe))
		{
			if(fgets(bufferComm, frameBodyLen, pipe) != NULL)
			{
				result->append( bufferComm );
			}
		}
	} 
	catch(...)
	{
		pclose(pipe);
		throw;
	}
	pclose(pipe);
	return _OK;
}

double stringToDouble( string str )
{
	double numb;
	istringstream( str ) >> numb;
	return numb;
}

int getdir( string dir, vector<string> &files )
{
    DIR *dp;
    struct dirent *dirp;
    if( (dp  = opendir(dir.c_str())) == NULL )
    {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return _ERROR;
    }


	string strDefa1(".");
	string strDefa2("..");
    while( (dirp = readdir(dp)) != NULL )
    {
		if( 
				dirp->d_name != strDefa1	&&
				dirp->d_name != strDefa2
		){		
			files.push_back(string(dirp->d_name));
		}
    }
    closedir(dp);
    return _OK;
}

int readSettings( structSettings* settings )
{
	string fileName;
	
	//Recording duration
    fileName = "./SETTINGS/audioDuration.parameter";//Seconds
	if( readFileContain( fileName, &settings->audioDuration ) != _OK )
	{
		cout << "[ERROR] Reading " << fileName << endl;
		return _ERROR;
	}
	
	//Sleep time as seconds
	fileName = "./SETTINGS/sleepTime.parameter";
	if( readFileContain( fileName, &settings->sleepTime ) != _OK )
	{
		cout << "[ERROR] Reading " << fileName << endl;
		return _ERROR;
	}
	
	//Reading Remote Folder
	fileName = "./SETTINGS/outputPath.parameter";
	if( readFileContain( fileName, &settings->outputPath ) != _OK )
	{
		cout << "[ERROR] Reading " << fileName << endl;
		return _ERROR;
	}
	
	return _OK;
	
}



int readFileContain( const string &fileName, string* contain )
{ 
	ifstream myfile ( fileName.c_str() );
	if( myfile.is_open() )
	{
		if( !getline( myfile, *contain ) )
		{
			return _FAIL;
		}
		myfile.close();
	}
	else
	{
		return _ERROR;
	}
	return _OK;
}
