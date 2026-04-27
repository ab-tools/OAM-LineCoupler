#include "LineCouplerModule.h"
#include "Logic.h"
#include "FunctionBlocksModule.h"
#include "FileTransferModule.h"

void setup()
{
    const uint8_t firmwareRevision = 0;
    openknx.init(firmwareRevision);
    openknx.addModule(1, openknxLogic);
    openknx.addModule(2, openknxLineCouplerModule);
    openknx.addModule(8, openknxFunctionBlocksModule);
    openknx.addModule(9, openknxFileTransferModule);
    openknx.setup();
}

void loop()
{
    openknx.loop();
}