#include "IO_wrapper.h"
#include "IO.h"
#include <stdint.h>
#include "errorhandler.h"
#include "sensoren.h"

static unsigned char dscrc_table[] = {
        0, 94, 188, 226, 97, 63, 221, 131, 194, 156, 126, 32, 163, 253, 31, 65,
        157, 195, 33, 127, 252, 162, 64, 30, 95, 1, 227, 189, 62, 96, 130, 220,
        35, 125, 159, 193, 66, 28, 254, 160, 225, 191, 93, 3, 128, 222, 60, 98,
        190, 224, 2, 92, 223, 129, 99, 61, 124, 34, 192, 158, 29, 67, 161, 255,
        70, 24, 250, 164, 39, 121, 155, 197, 132, 218, 56, 102, 229, 187, 89, 7,
        219, 133, 103, 57, 186, 228, 6, 88, 25, 71, 165, 251, 120, 38, 196, 154,
        101, 59, 217, 135, 4, 90, 184, 230, 167, 249, 27, 69, 198, 152, 122, 36,
        248, 166, 68, 26, 153, 199, 37, 123, 58, 100, 134, 216, 91, 5, 231, 185,
        140, 210, 48, 110, 237, 179, 81, 15, 78, 16, 242, 172, 47, 113, 147,
        205,
        17, 79, 173, 243, 112, 46, 204, 146, 211, 141, 111, 49, 178, 236, 14,
        80,
        175, 241, 19, 77, 206, 144, 114, 44, 109, 51, 209, 143, 12, 82, 176,
        238,
        50, 108, 142, 208, 83, 13, 239, 177, 240, 174, 76, 18, 145, 207, 45,
        115,
        202, 148, 118, 40, 171, 245, 23, 73, 8, 86, 180, 234, 105, 55, 213, 139,
        87, 9, 235, 181, 54, 104, 138, 212, 149, 203, 41, 119, 244, 170, 72, 22,
        233, 183, 85, 11, 136, 214, 52, 106, 43, 117, 151, 201, 74, 20, 246,
        168,
        116, 42, 200, 150, 21, 75, 169, 247, 182, 232, 10, 84, 215, 137, 107,
        53};

static uint8_t temperatur_bytes[8];

static unsigned char ROM_NO[8];

static int LastDiscrepancy;

static int LastFamilyDiscrepancy;

static int LastDeviceFlag;

static unsigned char crc8;


bool check_CRC(uint8_t *bytes, int anzahl) {
    uint8_t crc8 = 0;

    for (int i = 0; i < anzahl; ++i) {
        crc8 = dscrc_table[crc8 ^ bytes[i]];
    }
    return crc8 == 0;
}

void read_temperature(double *temperatur) {
    read_bytes(temperatur_bytes, 9);
    //ERR_HANDLER(!check_CRC(temperatur_bytes, 9), "CRC falsch");
    uint16_t temperatur_zwischenspeicher =
            temperatur_bytes[0] | (((uint16_t) temperatur_bytes[1]) << 8);

    /*tests
    temperatur_zwischenspeicher = 0xFF5E;
    temperatur_zwischenspeicher = 0xFC90;
    temperatur_zwischenspeicher = 0x07D0;
    */
    if ((0x01 << 15) & temperatur_zwischenspeicher) {
        temperatur_zwischenspeicher &= ~(0x01 << 15);
        *temperatur = -1 * (SENSOR_RESELUTION *
                            ((0x01 << 15) - temperatur_zwischenspeicher));
    } else {
        *temperatur = SENSOR_RESELUTION * temperatur_zwischenspeicher;
    }
}

//--------------------------------------------------------------------------
// Find the 'first' devices on the 1-Wire bus
// Return TRUE : device found, ROM number in ROM_NO buffer
// FALSE : no device present
//
int OWFirst() {
// reset the search state
    LastDiscrepancy = 0;
    LastDeviceFlag = FALSE;
    LastFamilyDiscrepancy = 0;
    return OWSearch();
}

//--------------------------------------------------------------------------
// Find the 'next' devices on the 1-Wire bus
// Return TRUE : device found, ROM number in ROM_NO buffer
// FALSE : device not found, end of search
//
int OWNext() {
// leave the search state alone
    return OWSearch();
}


void get_pdrom(uint8_t *pdrom) {
	for (int i = 0; i < 8; ++i) {
		pdrom[i] = ROM_NO[i];
	}

}

//--------------------------------------------------------------------------
// Perform the 1-Wire Search Algorithm on the 1-Wire bus using the existing
// search state.
// Return TRUE : device found, ROM number in ROM_NO buffer
// FALSE : device not found, end of search
//
int OWSearch() {
    int id_bit_number;
    int last_zero, rom_byte_number, search_result;
    int id_bit, cmp_id_bit;
    unsigned char rom_byte_mask, search_direction;
// initialize for search
    id_bit_number = 1;
    last_zero = 0;
    rom_byte_number = 0;
    rom_byte_mask = 1;
    search_result = 0;
    crc8 = 0;
// if the last call was not the last one
    if (!LastDeviceFlag) {
// 1-Wire reset
        if (!write_reset()) {
// reset the search
            LastDiscrepancy = 0;
            LastDeviceFlag = FALSE;
            LastFamilyDiscrepancy = 0;
            return FALSE;
        }
// issue the search command
        write_byte(0xF0);
// loop to do the search
        do {
// read a bit and its complement
            id_bit = read_bit();
            cmp_id_bit = read_bit();
// check for no devices on 1-wire
            if ((id_bit == 1) && (cmp_id_bit == 1))
                break;
            else {
// all devices coupled have 0 or 1
                if (id_bit != cmp_id_bit)
                    search_direction = id_bit; // bit write value for search
                else {
// if this discrepancy if before the Last Discrepancy
// on a previous next then pick the same as last time
                    if (id_bit_number < LastDiscrepancy)
                        search_direction = ((ROM_NO[rom_byte_number] &
                                             rom_byte_mask) > 0);
                    else
// if equal to last pick 1, if not then pick 0
                        search_direction = (id_bit_number == LastDiscrepancy);
// if 0 was picked then record its position in LastZero
                    if (search_direction == 0) {
                        last_zero = id_bit_number;
// check for Last discrepancy in family
                        if (last_zero < 9)
                            LastFamilyDiscrepancy = last_zero;
                    }
                }
// set or clear the bit in the ROM byte rom_byte_number
// with mask rom_byte_mask
                if (search_direction == 1)
                    ROM_NO[rom_byte_number] |= rom_byte_mask;
                else
                    ROM_NO[rom_byte_number] &= ~rom_byte_mask;
// serial number search direction write bit
                write_bit(search_direction);
// increment the byte counter id_bit_number
// and shift the mask rom_byte_mask
                id_bit_number++;
                rom_byte_mask <<= 1;
// if the mask is 0 then go to new SerialNum byte rom_byte_number and reset mask
                if (rom_byte_mask == 0) {
                    // accumulate the CRC
                    rom_byte_number++;
                    rom_byte_mask = 1;
                }
            }
        } while (rom_byte_number < 8); // loop until through all ROM bytes 0-7
// if the search was successful then
        if (!(id_bit_number < 65)) {
// search successful so set LastDiscrepancy,LastDeviceFlag,search_result
            LastDiscrepancy = last_zero;
// check for last device
            if (LastDiscrepancy == 0) {
                LastDeviceFlag = TRUE;
						}
            search_result = TRUE;
        }
    }
// if no device found then reset counters so next 'search' will be like afirst
    if (!search_result || !ROM_NO[0]) {
        LastDiscrepancy = 0;
        LastDeviceFlag = FALSE;
        LastFamilyDiscrepancy = 0;
        search_result = FALSE;
    }
    return search_result;
}