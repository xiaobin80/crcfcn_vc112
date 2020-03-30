/**
 * \file
 *
 * \brief File head define
 *
 * <table>
 * <tr><th>Version</th><th>Author</th><th>Date</th>
 * <tr><td>1.1</td><td>Guibin.Li</td><td>2009.09.20</td>
 * </table>
 *
 * \page License
 *
 *   Copyright (c) 2013-2020 Tdtc Corporation. All rights reserved.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 */

#pragma pack(4)

struct TFileHead {
	char Version[10];
	char author[10];
	unsigned long CRC32;
 	char UpdateDate[10];
}FileHead, *PTFileHead;
