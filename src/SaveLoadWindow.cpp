#include "SaveLoadWindow.h"

#include "cinder/Json.h"

namespace reza {
namespace win {

void saveWindow( const ci::fs::path &path, const glm::ivec2 &origin, const glm::ivec2 &size, bool valid )
{
	ci::JsonTree tree;
	tree.addChild( ci::JsonTree( "X", ( origin.x < 3000 && origin.x > 0 ) ? origin.x : 0 ) );
	tree.addChild( ci::JsonTree( "Y", ( origin.y < 3000 && origin.y > 0 ) ? origin.y : 0 ) );
	tree.addChild( ci::JsonTree( "W", ( size.x < 3000 && size.x > 0 ) ? size.x : 212 ) );
	tree.addChild( ci::JsonTree( "H", ( size.y < 3000 && size.y > 0 ) ? size.y : 212 ) );
	tree.addChild( ci::JsonTree( "V", valid ) );
	tree.write( path );
}

void loadWindow( const ci::fs::path &path, bool closeable, const std::function<void( glm::ivec2, glm::ivec2, bool )> &cb )
{
	if( ci::fs::exists( path ) ) {
		try {
			ci::JsonTree tree( ci::loadFile( path ) );
			if( tree.hasChildren() ) {
				try {
					glm::ivec2 pos( tree.getValueForKey<int>( "X" ), tree.getValueForKey<int>( "Y" ) );
					glm::ivec2 size( tree.getValueForKey<int>( "W" ), tree.getValueForKey<int>( "H" ) );

					pos.x = ( pos.x < 3000 && pos.x > 0 ) ? pos.x : 0;
					pos.y = ( pos.y < 3000 && pos.y > 0 ) ? pos.y : 0;

					size.x = ( size.x < 3000 && size.x > 0 ) ? size.x : 212;
					size.y = ( size.y < 3000 && size.y > 0 ) ? size.y : 212;

					bool valid = tree.getValueForKey<bool>( "V" );
					if( cb != nullptr ) {
						cb( pos, size, valid );
					}
				}
				catch( ci::Exception &exc ) {
					std::cout << "LOAD WINDOW ERROR: " << exc.what() << std::endl;
				}
			}
		}
		catch( ci::Exception exc ) {
			std::cout << "LOAD WINDOW ERROR: " << exc.what() << std::endl;
		}
	}
}
} // namespace win
} // namespace reza
