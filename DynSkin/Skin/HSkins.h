#ifndef _HSKINS_H_
#define _HSKINS_H_

#pragma once

#include "..\File\Valve\HValve.h"

#pragma warning(disable : 4227)

namespace Skins
{

	struct SkinInfo_t
	{


		unsigned int	_id;			// index u know for what

		std::string		_shortname;		// shortname
		std::string		_name;			// full skin name
	};

	typedef std::vector< SkinInfo_t >						vecSkinInfo;
	typedef std::unordered_map< std::string, vecSkinInfo >	mapSkinInfo;

	class CSkins
	{

	public:

												CSkins( void );
												~CSkins( void );


	public:

		bool									Load( void );
		void									Release( void );


	public:

		void									Dump( std::ofstream& dump );


	public:

		inline const mapSkinInfo& const			GetSkinInfo( void )								{ return _skininfo; }
		inline const vecSkinInfo& const			GetSkinInfoByWeapon( const std::string& weapon ){
			auto& ret = _skininfo.find( weapon );
			if( ret != _skininfo.end( ) )
				return ret->second;
			return vecSkinInfo( );
		}
		

	protected:

		File::Valve::CConfig*					_items_game = 0;	// config file by valve
		File::Valve::CConfig*					_csgo_english = 0;	// config file by valve

		mapSkinInfo								_skininfo;			// Holds Skinsinformation
	};
}

#pragma warning(default : 4227)

#endif /* _HSKINS_H_ */