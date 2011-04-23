/*
 * Types.h
 *
 *  Created on: 27 Dec 2010
 *      Author: Michael
 */

#ifndef TYPES_H_
#define TYPES_H_
namespace Planar {
	namespace Types {
			namespace Numeric {
				static const size_t Short 	 	  = sizeof(short);
				static const size_t Integer 	  = sizeof(int);
				static const size_t Float		  = sizeof(float);
				static const size_t Double		  = sizeof(double);
			}

			namespace Text {
				static const size_t Sentence  = sizeof(char) * 200;
				static const size_t Paragraph = sizeof(char) * 1000;
				static const size_t Page	  = sizeof(char) * 10000;
				static const size_t Attribute = sizeof(char) * 100;
			}

			namespace Special {
				struct DateTime {
					unsigned short day, month, year;
					unsigned short hour, minute, second;
				};

				static const size_t DtTime = sizeof(DateTime);
				static const size_t Bool   = sizeof(char);
				static const size_t Byte   = sizeof(char);
				static const size_t KibiByte   = sizeof(char) * 1024;
				static const size_t MebiByte   = sizeof(char) * 1024 * 1024;

//				static const size_t Blob ; TODO: Support
			}
	}
}

#endif /* TYPES_H_ */
