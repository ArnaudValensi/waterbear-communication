/* ***** BEGIN LICENSE BLOCK *****
 *
 * This file is part of arduino-control-interface.
 *
 * arduino-control-interface is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * arduino-control-interface is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with arduino-control-interface.  If not, see <http://www.gnu.org/licenses/>.
 *
 * ***** END LICENSE BLOCK ***** */

//--------------------------------------------------------
// TYPE DEFINITION
//--------------------------------------------------------
typedef struct {
  uint8_t pin;
  uint8_t value;
} 
__attribute__((__packed__))data_packet_t;

//--------------------------------------------------------
// INIT VARIABLES
//--------------------------------------------------------
data_packet_t data;

//--------------------------------------------------------
// ARDUINO FUNCTIONS
//--------------------------------------------------------
void setup() {
  Serial.begin(9600);
  for(int i = 0; i < 14; ++i)
    pinMode(i, INPUT);
}

void loop() {
  unsigned long buffer_size = sizeof(data_packet_t);
  char buffer[buffer_size];

  if (Serial.readBytes(buffer, buffer_size) > 0)
  { 
    memcpy(&data, buffer, buffer_size);

    Serial.print("pin: ");
    Serial.print(data.pin);
    Serial.print("value: ");
    Serial.println(data.value);
  }
}

