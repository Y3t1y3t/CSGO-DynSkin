#include "HMain.h"

int main( )
{

	Skins::CSkins* pSkins = new Skins::CSkins( );
	if( pSkins->Load( ) ){
		pSkins->Dump( std::ofstream("C:\\skins.txt") );
	}

	delete pSkins;

	system( "pause" );
}