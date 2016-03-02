#include "networktables/NetworkTable.h"

static void testNTs() {
        NetworkTable::SetClientMode();
        NetworkTable::SetIPAddress("192.156.1.100");
        NetworkTable::Initialize();

        std::shared_ptr<NetworkTable> table = NetworkTable::GetTable("table");
	table->PutNumber("hi", 2);
}
