#include <iostream>
#include "include/receiver/receiverwrapper.h"

#include <vector>

using namespace std;

// AGC mode changed to on
// fake: complex and spectrum writing in file and have 2nd version (withtout settings)
// real: complex and spectrum writing in file and have 2nd version (withtout settings)
// real: working correct, write complex on Fc=0
// fake: working correct, but GenW is uncorrect


int main() {


// auto reImpl = ReceiverWrapper::getReceiverByName( "hw" );
// uint32_t centralFreq = 104200000;
// uint32_t sampleFreq = 960000;
// RfSettings sett { centralFreq, sampleFreq, 490 };

// ReceiverSettings recset;
// recset.sampleCount = ( uint32_t )1024; // must be 512 or higher 4194304
// recset.rfSettings = sett;
// BaseSettings* rp = &recset;
// reImpl->setSettings( rp );

// std::vector< Complex< uint8_t > > Buf;

// std::vector< Complex< double > > SpBuf;
// reImpl->getSpectrum( rp, SpBuf );

// std::ofstream fileOut( "/home/ann/WORK/work_mtlb/comsig.iqc", std::fstream::binary );
// std::ofstream fileOut222( "/home/ann/WORK/work_mtlb/comsig.iqc", std::fstream::binary );

// for( uint32_t i = 0; i < 1; i++ ) {
// reImpl->getComplex( Buf );
// uint32_t N = Buf.size();
// fileOut.write( ( char* )( Buf.data() ), sizeof( uint8_t ) * 2 * N );

// }
// fileOut.close();

// for( uint32_t i = 0; i < 1; i++ ) {
// reImpl->getSpectrum( SpBuf );
// uint32_t N = SpBuf.size();
// fileOut222.write( ( char* )( SpBuf.data() ), sizeof( double ) * 2 * N );

// }
// fileOut.close();


    sinParams sin1 { 6, 10 };
    sinParams sin2 { 0, 30 };
    sinParams sin3 { 0, 30 };

    auto fakeImpl = ReceiverWrapper::getReceiverByName( "fake" );


    fakeParams fakeset;
    fakeset.fd = 1600;
    fakeset.sampleCount = 1600;
    fakeset.noiseLVL = 18;

    fakeset.sinPar = { sin1, sin2, sin3 };

    BaseSettings* fp = &fakeset;
    fakeImpl->setSettings( fp );

    std::vector< Complex< uint8_t > > Buf2;
    fakeImpl->getComplex(  Buf2 );

    std::vector< Complex< double > > SpecBuf;
    fakeImpl->getSpectrum(  SpecBuf );

    uint32_t N2 = Buf2.size();
    uint32_t SpN2 = SpecBuf.size();

    std::ofstream ComfileOut( "/home/ann/WORK/work_mtlb/comsig1.iqc", std::fstream::binary );
    ComfileOut.write( ( char* )( Buf2.data() ), sizeof( uint8_t ) * 2 * N2 );
    ComfileOut.close();

    std::ofstream SpecfileOut( "/home/ann/WORK/work_mtlb/comsig2.iqc", std::fstream::binary );
    SpecfileOut.write( ( char* )( SpecBuf.data() ), sizeof( double ) * 2 * SpN2 );
    SpecfileOut.close();

    return 0;
}

