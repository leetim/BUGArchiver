#include <fstream>
#include <iostream>
#include <string>
#include "input.h"
#include "anyoption.h"

using namespace std;

void using_any_option(int argc, char* argv[], data* input_data)
{
    AnyOption *opt = new AnyOption();
    opt->addUsage( "" );
    opt->addUsage( "HELP" );
    opt->addUsage( "" );
    opt->addUsage( " -h     --help          Help " );
    opt->addUsage( " -i     --input         Name of input file " );
    opt->addUsage( " -o     --output        Name of output file " );
    opt->addUsage( " -a    --algorithm      Type of algorithm n or h (nope or huffman)" );
    opt->addUsage( " -t     --type          Type of operation c or d (compress or decompress)" );
    opt->addUsage( "" );

    opt->setFlag(  "help", 'h' );
    opt->setOption(  "input", 'i' );
    opt->setOption(  "output", 'o' );
    opt->setOption(  "type", 't' );
    opt->processCommandArgs( argc, argv );

    if( opt->getFlag( "help" ) || opt->getFlag( 'h' ) )
    {
        opt->printUsage();
    }
    if( opt->getValue( 'i' ) != NULL  || opt->getValue( "input" ) != NULL  )
    {
        input_data->input.push_back(opt->getValue('i'));
        input_data->fcount++;
    }
    if( opt->getValue( 'o' ) != NULL  || opt->getValue( "output" ) != NULL  )
    {
        input_data->output=opt->getValue('o');
    }else
    {
        input_data->output="output.bug";
    }
    if( opt->getValue( 'a' ) != NULL  || opt->getValue( "algorithm" ) != NULL  )
    {
        input_data->alg=opt->getValue('a');
    }else
    {
        input_data->alg="h";
    }
    if( opt->getValue( 't' ) != NULL  || opt->getValue( "type" ) != NULL  )
    {
        input_data->type=opt->getValue('t');
    }else
    {
        input_data->type="c";
    }
    for( int i = 0 ; i < opt->getArgc() ; i++ )
    {
        cout << "wrong arg = " <<  opt->getArgv( i ) << ";";
    }
    delete opt;
}

bool reading(data* input_data, vector<Byte>& buffer) // ���������� true, ���� ������
{
    ifstream inf;
    for(int i=0; i<input_data->fcount; i++)
    {
        inf.open(input_data->input[i], ios::binary);
        if(!inf)
        return true;
        Byte temp;
        while(!inf.eof())
        {
            inf >> temp;
            buffer.push_back(temp);
        }
    }
    return false;
}
