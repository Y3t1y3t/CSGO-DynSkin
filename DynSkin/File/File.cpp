#include "HFile.h"


namespace File
{

	CFile::CFile( void )
	{

		_instance = this;
	}

	CFile::~CFile( void )
	{
	}

	bool CFile::Load( const std::string& szPath, bool isunicode /* = false*/ )
	{

		Release( );

		if( GetFileAttributesA( szPath.c_str( ) ) == 0xFFFFFFFF )//sanity check
			return false;

		_szPath = szPath;

		std::ifstream ifs( _szPath, std::ios::binary | std::ios::ate );
		std::ifstream::pos_type pos = ifs.tellg( );

		vecFile tmp = vecFile( szPos( pos ) );

		ifs.seekg( 0, std::ios::beg );
		ifs.read( &tmp.at( 0 ), pos );

		if( isunicode ){
			for( unsigned int i = 0; i < pos; i += 2 )
				_file.push_back( tmp.at( i ) );
		}
		else
			_file = tmp;

		return Parse( );
	}

	void CFile::Release( void )
	{

		if( !_file.empty( ) )
			_file.clear( );

		_szPath.clear( );
	}

	szPos CFile::FindFirstOf( const std::string& szSearch, szPos start, szPos end )
	{

		bool isInverse = bool( start > end );

		if( _file.size( ) <= ( isInverse ? start : end ) )
			return _file.size( );

		if( isInverse ){
			for( szPos r = start; r > end; --r ){
				if( CompareBytes( ( char* ) &_file.at( r ), ( char* ) &szSearch.at( 0 ) ) )
					return r;
			}
		}
		else{
			for( szPos r = start; r < end; ++r ){
				if( CompareBytes( ( char* ) &_file.at( r ), ( char* ) &szSearch.at( 0 ) ) )
					return r;
			}
		}

		return _file.size( );
	}

	vecPos CFile::FindAllOf( const std::string& szSearch, szPos start, szPos end, vecPos pos /*= vecPos( )*/ )
	{

		bool isInverse = bool( start > end );

		if( _file.size( ) <= ( isInverse ? start : end ) )
			return pos;

		if( isInverse ){
			for( szPos r = start; r > end; --r ){
				if( CompareBytes( ( char* ) &_file.at( r ), ( char* ) &szSearch.at( 0 ) ) )
					pos.push_back( r );
			}
		}
		else{
			for( szPos r = start; r < end; ++r ){
				if( CompareBytes( ( char* ) &_file.at( r ), ( char* ) &szSearch.at( 0 ) ) )
					pos.push_back( r );
			}
		}

		return pos;
	}

	std::string CFile::GetStringAt( szPos start, szSize length )
	{

		if( _file.size( ) <= ( start + length ) )
			return std::string( "" );

		return std::string( ( char* ) &_file.at( start ), length );
	}

	std::string CFile::GetStringBetween( szPos start, szPos end )
	{

		bool isInverse = bool( start > end );

		if( _file.size( ) <= ( isInverse ? start : end ) )
			return std::string( "" );

		szPos rstart = isInverse ? end : start;
		szPos rend = isInverse ? start : end;

		return std::string( ( char* ) &_file.at( rstart ), szPos( rend - rstart ) );
	}
}