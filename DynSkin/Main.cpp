#include "HMain.h"

int main( )
{
    auto pSkins = new Skins::CSkins( );
    if( pSkins->Load( "..\Counter-Strike: Global Offensive", "csgo" ) ) {
        pSkins->Dump( std::ofstream( "C:\\skins.txt" ) );
    }

    delete pSkins;
    system( "pause" );
}