#include "MovementStructures434.h"
#include "Opcodes.h"
#include "WorldServer.h"

MovementStatusElements const MovementUpdate[] =
{
    MSEHasFallData,
    MSEHasGuidByte3,
    MSEHasGuidByte6,
    MSEHasMovementFlags2,
    MSEHasSpline,
    MSEHasTimestamp,
    MSEHasGuidByte0,
    MSEHasGuidByte1,
    MSEMovementFlags2,
    MSEHasGuidByte7,
    MSEHasMovementFlags,
    MSEHasOrientation,
    MSEHasGuidByte2,
    MSEHasSplineElevation,
    MSEHasHeightChangeFailed,
    MSEHasGuidByte4,
    MSEHasFallDirection,
    MSEHasGuidByte5,
    MSEHasTransportData,
    MSEMovementFlags,
    MSEHasTransportGuidByte3,
    MSEHasVehicleId,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte4,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte2,
    MSEHasPitch,
    MSEFlushBits,
    MSEGuidByte5,
    MSEFallHorizontalSpeed,
    MSEFallSinAngle,
    MSEFallCosAngle,
    MSEFallVerticalSpeed,
    MSEFallTime,
    MSESplineElevation,
    MSEGuidByte7,
    MSEPositionY,
    MSEGuidByte3,
    MSETransportVehicleId,
    MSETransportGuidByte6,
    MSETransportSeat,
    MSETransportGuidByte5,
    MSETransportPositionX,
    MSETransportGuidByte1,
    MSETransportOrientation,
    MSETransportGuidByte2,
    MSETransportTime2,
    MSETransportGuidByte0,
    MSETransportPositionZ,
    MSETransportGuidByte7,
    MSETransportGuidByte4,
    MSETransportGuidByte3,
    MSETransportPositionY,
    MSETransportTime,
    MSEGuidByte4,
    MSEPositionX,
    MSEGuidByte6,
    MSEPositionZ,
    MSETimestamp,
    MSEGuidByte2,
    MSEPitch,
    MSEGuidByte0,
    MSEOrientation,
    MSEGuidByte1,
    MSEEnd
};

MovementStatusElements const MovementFallLand[] =
{
    MSEPositionX,
    MSEPositionY,
    MSEPositionZ,
    MSEHasTransportData,
    MSEHasGuidByte7,
    MSEHasGuidByte1,
    MSEHasMovementFlags2,
    MSEHasGuidByte3,
    MSEHasSplineElevation,
    MSEHasOrientation,
    MSEHasGuidByte6,
    MSEHasTimestamp,
    MSEZeroBit,
    MSEHasPitch,
    MSEHasGuidByte4,
    MSEHasSpline,
    MSEHasGuidByte5,
    MSEHasMovementFlags,
    MSEHasFallData,
    MSEHasGuidByte0,
    MSEHasGuidByte2,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte2,
    MSEHasVehicleId,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte7,
    MSEMovementFlags2,
    MSEMovementFlags,
    MSEHasFallDirection,
    MSEGuidByte1,
    MSEGuidByte7,
    MSEGuidByte4,
    MSEGuidByte3,
    MSEGuidByte6,
    MSEGuidByte0,
    MSEGuidByte2,
    MSEGuidByte5,
    MSETransportTime,
    MSETransportPositionZ,
    MSETransportPositionY,
    MSETransportPositionX,
    MSETransportGuidByte5,
    MSETransportVehicleId,
    MSETransportGuidByte1,
    MSETransportSeat,
    MSETransportTime2,
    MSETransportGuidByte4,
    MSETransportOrientation,
    MSETransportGuidByte0,
    MSETransportGuidByte7,
    MSETransportGuidByte3,
    MSETransportGuidByte6,
    MSETransportGuidByte2,
    MSEFallVerticalSpeed,
    MSEFallTime,
    MSEFallSinAngle,
    MSEFallHorizontalSpeed,
    MSEFallCosAngle,
    MSESplineElevation,
    MSETimestamp,
    MSEPitch,
    MSEOrientation,
    MSEEnd,
};

MovementStatusElements const MovementHeartBeat[] =
{
    MSEPositionZ,
    MSEPositionX,
    MSEPositionY,
    MSEHasPitch,
    MSEHasTimestamp,
    MSEHasFallData,
    MSEHasMovementFlags2,
    MSEHasTransportData,
    MSEHasGuidByte7,
    MSEHasGuidByte1,
    MSEHasGuidByte0,
    MSEHasGuidByte4,
    MSEHasGuidByte2,
    MSEHasOrientation,
    MSEHasGuidByte5,
    MSEHasGuidByte3,
    MSEHasSplineElevation,
    MSEHasSpline,
    MSEZeroBit,
    MSEHasGuidByte6,
    MSEHasMovementFlags,
    MSEHasVehicleId,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte2,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte1,
    MSEHasFallDirection,
    MSEMovementFlags,
    MSEMovementFlags2,
    MSEGuidByte3,
    MSEGuidByte6,
    MSEGuidByte1,
    MSEGuidByte7,
    MSEGuidByte2,
    MSEGuidByte5,
    MSEGuidByte0,
    MSEGuidByte4,
    MSETransportPositionZ,
    MSETransportSeat,
    MSETransportOrientation,
    MSETransportGuidByte4,
    MSETransportPositionY,
    MSETransportTime,
    MSETransportPositionX,
    MSETransportGuidByte5,
    MSETransportGuidByte1,
    MSETransportGuidByte3,
    MSETransportGuidByte7,
    MSETransportVehicleId,
    MSETransportTime2,
    MSETransportGuidByte2,
    MSETransportGuidByte0,
    MSETransportGuidByte6,
    MSEOrientation,
    MSEFallVerticalSpeed,
    MSEFallTime,
    MSEFallHorizontalSpeed,
    MSEFallCosAngle,
    MSEFallSinAngle,
    MSEPitch,
    MSESplineElevation,
    MSETimestamp,
    MSEEnd,
};

MovementStatusElements const MovementJump[] =
{
    MSEPositionY,
    MSEPositionX,
    MSEPositionZ,
    MSEHasTimestamp,
    MSEHasGuidByte5,
    MSEHasMovementFlags,
    MSEHasGuidByte4,
    MSEHasGuidByte6,
    MSEHasMovementFlags2,
    MSEHasGuidByte0,
    MSEHasTransportData,
    MSEHasGuidByte3,
    MSEHasPitch,
    MSEHasGuidByte7,
    MSEHasFallData,
    MSEHasSpline,
    MSEHasOrientation,
    MSEHasGuidByte1,
    MSEHasSplineElevation,
    MSEZeroBit,
    MSEHasGuidByte2,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte4,
    MSEHasVehicleId,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte2,
    MSEHasFallDirection,
    MSEMovementFlags,
    MSEMovementFlags2,
    MSEGuidByte6,
    MSEGuidByte5,
    MSEGuidByte4,
    MSEGuidByte0,
    MSEGuidByte2,
    MSEGuidByte3,
    MSEGuidByte7,
    MSEGuidByte1,
    MSETransportGuidByte1,
    MSETransportGuidByte7,
    MSETransportPositionX,
    MSETransportGuidByte4,
    MSETransportVehicleId,
    MSETransportGuidByte0,
    MSETransportOrientation,
    MSETransportTime2,
    MSETransportTime,
    MSETransportGuidByte6,
    MSETransportPositionZ,
    MSETransportSeat,
    MSETransportPositionY,
    MSETransportGuidByte3,
    MSETransportGuidByte2,
    MSETransportGuidByte5,
    MSEPitch,
    MSETimestamp,
    MSEFallSinAngle,
    MSEFallCosAngle,
    MSEFallHorizontalSpeed,
    MSEFallVerticalSpeed,
    MSEFallTime,
    MSESplineElevation,
    MSEOrientation,
    MSEEnd,
};

MovementStatusElements const MovementSetFacing[] =
{
    MSEPositionX,
    MSEPositionY,
    MSEPositionZ,
    MSEHasGuidByte6,
    MSEHasTransportData,
    MSEHasGuidByte4,
    MSEHasSpline,
    MSEHasGuidByte0,
    MSEHasOrientation,
    MSEHasTimestamp,
    MSEHasPitch,
    MSEHasMovementFlags2,
    MSEHasGuidByte5,
    MSEHasGuidByte7,
    MSEHasGuidByte2,
    MSEHasFallData,
    MSEHasSplineElevation,
    MSEHasMovementFlags,
    MSEHasGuidByte3,
    MSEZeroBit,
    MSEHasGuidByte1,
    MSEHasVehicleId,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte0,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte1,
    MSEHasFallDirection,
    MSEMovementFlags2,
    MSEMovementFlags,
    MSEGuidByte6,
    MSEGuidByte7,
    MSEGuidByte2,
    MSEGuidByte0,
    MSEGuidByte4,
    MSEGuidByte1,
    MSEGuidByte5,
    MSEGuidByte3,
    MSETransportGuidByte0,
    MSETransportPositionX,
    MSETransportGuidByte1,
    MSETransportTime2,
    MSETransportGuidByte4,
    MSETransportPositionZ,
    MSETransportOrientation,
    MSETransportGuidByte2,
    MSETransportVehicleId,
    MSETransportGuidByte3,
    MSETransportSeat,
    MSETransportPositionY,
    MSETransportGuidByte5,
    MSETransportGuidByte6,
    MSETransportTime,
    MSETransportGuidByte7,
    MSEFallHorizontalSpeed,
    MSEFallCosAngle,
    MSEFallSinAngle,
    MSEFallTime,
    MSEFallVerticalSpeed,
    MSESplineElevation,
    MSEOrientation,
    MSETimestamp,
    MSEPitch,
    MSEEnd,
};

MovementStatusElements const MovementSetPitch[] =
{
    MSEPositionX,
    MSEPositionZ,
    MSEPositionY,
    MSEHasFallData,
    MSEHasMovementFlags,
    MSEHasGuidByte1,
    MSEHasOrientation,
    MSEHasGuidByte7,
    MSEHasGuidByte3,
    MSEHasMovementFlags2,
    MSEHasTransportData,
    MSEHasSplineElevation,
    MSEHasGuidByte6,
    MSEHasPitch,
    MSEHasGuidByte4,
    MSEHasSpline,
    MSEHasGuidByte2,
    MSEZeroBit,
    MSEHasTimestamp,
    MSEHasGuidByte0,
    MSEHasGuidByte5,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte5,
    MSEHasVehicleId,
    MSEHasTransportGuidByte7,
    MSEHasTransportTime2,
    MSEMovementFlags2,
    MSEMovementFlags,
    MSEHasFallDirection,
    MSEGuidByte3,
    MSEGuidByte7,
    MSEGuidByte1,
    MSEGuidByte6,
    MSEGuidByte0,
    MSEGuidByte5,
    MSEGuidByte2,
    MSEGuidByte4,
    MSETransportGuidByte4,
    MSETransportGuidByte3,
    MSETransportGuidByte6,
    MSETransportOrientation,
    MSETransportGuidByte1,
    MSETransportVehicleId,
    MSETransportTime,
    MSETransportGuidByte2,
    MSETransportPositionZ,
    MSETransportGuidByte0,
    MSETransportTime2,
    MSETransportPositionY,
    MSETransportGuidByte5,
    MSETransportSeat,
    MSETransportGuidByte7,
    MSETransportPositionX,
    MSEFallVerticalSpeed,
    MSEFallTime,
    MSEFallHorizontalSpeed,
    MSEFallSinAngle,
    MSEFallCosAngle,
    MSEPitch,
    MSESplineElevation,
    MSETimestamp,
    MSEOrientation,
    MSEEnd,
};

MovementStatusElements const MovementStartBackward[] =
{
    MSEPositionX,
    MSEPositionZ,
    MSEPositionY,
    MSEHasTransportData,
    MSEHasGuidByte3,
    MSEHasGuidByte0,
    MSEHasGuidByte2,
    MSEHasTimestamp,
    MSEHasGuidByte7,
    MSEHasPitch,
    MSEZeroBit,
    MSEHasMovementFlags,
    MSEHasOrientation,
    MSEHasSpline,
    MSEHasMovementFlags2,
    MSEHasFallData,
    MSEHasGuidByte5,
    MSEHasGuidByte1,
    MSEHasGuidByte4,
    MSEHasGuidByte6,
    MSEHasSplineElevation,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte1,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte4,
    MSEHasVehicleId,
    MSEMovementFlags,
    MSEMovementFlags2,
    MSEHasFallDirection,
    MSEGuidByte6,
    MSEGuidByte7,
    MSEGuidByte4,
    MSEGuidByte1,
    MSEGuidByte5,
    MSEGuidByte0,
    MSEGuidByte2,
    MSEGuidByte3,
    MSETransportPositionZ,
    MSETransportGuidByte2,
    MSETransportVehicleId,
    MSETransportGuidByte0,
    MSETransportGuidByte5,
    MSETransportPositionY,
    MSETransportGuidByte1,
    MSETransportPositionX,
    MSETransportTime2,
    MSETransportGuidByte4,
    MSETransportOrientation,
    MSETransportSeat,
    MSETransportGuidByte7,
    MSETransportTime,
    MSETransportGuidByte6,
    MSETransportGuidByte3,
    MSEPitch,
    MSETimestamp,
    MSEFallHorizontalSpeed,
    MSEFallCosAngle,
    MSEFallSinAngle,
    MSEFallVerticalSpeed,
    MSEFallTime,
    MSEOrientation,
    MSESplineElevation,
    MSEEnd,
};

MovementStatusElements const MovementStartForward[] =
{
    MSEPositionY,
    MSEPositionZ,
    MSEPositionX,
    MSEHasGuidByte5,
    MSEHasGuidByte2,
    MSEHasGuidByte0,
    MSEZeroBit,
    MSEHasMovementFlags,
    MSEHasGuidByte7,
    MSEHasGuidByte3,
    MSEHasGuidByte1,
    MSEHasOrientation,
    MSEHasGuidByte6,
    MSEHasSpline,
    MSEHasSplineElevation,
    MSEHasGuidByte4,
    MSEHasTransportData,
    MSEHasTimestamp,
    MSEHasPitch,
    MSEHasMovementFlags2,
    MSEHasFallData,
    MSEMovementFlags,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte1,
    MSEHasVehicleId,
    MSEHasTransportTime2,
    MSEHasFallDirection,
    MSEMovementFlags2,
    MSEGuidByte2,
    MSEGuidByte4,
    MSEGuidByte6,
    MSEGuidByte1,
    MSEGuidByte7,
    MSEGuidByte3,
    MSEGuidByte5,
    MSEGuidByte0,
    MSEFallVerticalSpeed,
    MSEFallHorizontalSpeed,
    MSEFallSinAngle,
    MSEFallCosAngle,
    MSEFallTime,
    MSETransportGuidByte3,
    MSETransportPositionY,
    MSETransportPositionZ,
    MSETransportGuidByte1,
    MSETransportGuidByte4,
    MSETransportGuidByte7,
    MSETransportOrientation,
    MSETransportGuidByte2,
    MSETransportPositionX,
    MSETransportGuidByte5,
    MSETransportVehicleId,
    MSETransportTime,
    MSETransportGuidByte6,
    MSETransportGuidByte0,
    MSETransportSeat,
    MSETransportTime2,
    MSESplineElevation,
    MSEPitch,
    MSEOrientation,
    MSETimestamp,
    MSEEnd,
};

MovementStatusElements const MovementStartStrafeLeft[] =
{
    MSEPositionZ,
    MSEPositionX,
    MSEPositionY,
    MSEHasSplineElevation,
    MSEHasGuidByte5,
    MSEHasPitch,
    MSEHasGuidByte6,
    MSEHasTimestamp,
    MSEHasGuidByte1,
    MSEZeroBit,
    MSEHasGuidByte4,
    MSEHasGuidByte0,
    MSEHasGuidByte2,
    MSEHasFallData,
    MSEHasOrientation,
    MSEHasGuidByte3,
    MSEHasMovementFlags2,
    MSEHasGuidByte7,
    MSEHasSpline,
    MSEHasMovementFlags,
    MSEHasTransportData,
    MSEHasFallDirection,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte7,
    MSEHasVehicleId,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte0,
    MSEMovementFlags,
    MSEMovementFlags2,
    MSEGuidByte2,
    MSEGuidByte6,
    MSEGuidByte3,
    MSEGuidByte1,
    MSEGuidByte0,
    MSEGuidByte7,
    MSEGuidByte4,
    MSEGuidByte5,
    MSEFallCosAngle,
    MSEFallHorizontalSpeed,
    MSEFallSinAngle,
    MSEFallTime,
    MSEFallVerticalSpeed,
    MSETransportSeat,
    MSETransportGuidByte2,
    MSETransportTime2,
    MSETransportGuidByte3,
    MSETransportPositionZ,
    MSETransportVehicleId,
    MSETransportGuidByte0,
    MSETransportGuidByte7,
    MSETransportPositionY,
    MSETransportGuidByte5,
    MSETransportGuidByte1,
    MSETransportOrientation,
    MSETransportTime,
    MSETransportGuidByte6,
    MSETransportGuidByte4,
    MSETransportPositionX,
    MSETimestamp,
    MSEOrientation,
    MSEPitch,
    MSESplineElevation,
    MSEEnd,
};

MovementStatusElements const MovementStartStrafeRight[] =
{
    MSEPositionY,
    MSEPositionX,
    MSEPositionZ,
    MSEHasPitch,
    MSEHasGuidByte1,
    MSEHasOrientation,
    MSEHasGuidByte4,
    MSEHasSpline,
    MSEZeroBit,
    MSEHasGuidByte5,
    MSEHasFallData,
    MSEHasSplineElevation,
    MSEHasTimestamp,
    MSEHasMovementFlags,
    MSEHasGuidByte2,
    MSEHasGuidByte7,
    MSEHasGuidByte6,
    MSEHasGuidByte3,
    MSEHasMovementFlags2,
    MSEHasTransportData,
    MSEHasGuidByte0,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte0,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte4,
    MSEHasVehicleId,
    MSEMovementFlags2,
    MSEMovementFlags,
    MSEHasFallDirection,
    MSEGuidByte7,
    MSEGuidByte5,
    MSEGuidByte3,
    MSEGuidByte1,
    MSEGuidByte2,
    MSEGuidByte4,
    MSEGuidByte6,
    MSEGuidByte0,
    MSETransportGuidByte5,
    MSETransportGuidByte1,
    MSETransportGuidByte6,
    MSETransportPositionY,
    MSETransportOrientation,
    MSETransportGuidByte0,
    MSETransportGuidByte2,
    MSETransportSeat,
    MSETransportPositionX,
    MSETransportVehicleId,
    MSETransportTime,
    MSETransportGuidByte4,
    MSETransportGuidByte7,
    MSETransportTime2,
    MSETransportPositionZ,
    MSETransportGuidByte3,
    MSEPitch,
    MSEOrientation,
    MSEFallSinAngle,
    MSEFallCosAngle,
    MSEFallHorizontalSpeed,
    MSEFallTime,
    MSEFallVerticalSpeed,
    MSETimestamp,
    MSESplineElevation,
    MSEEnd,
};

MovementStatusElements const MovementStartTurnLeft[] =
{
    MSEPositionY,
    MSEPositionX,
    MSEPositionZ,
    MSEZeroBit,
    MSEHasGuidByte1,
    MSEHasOrientation,
    MSEHasSpline,
    MSEHasMovementFlags,
    MSEHasGuidByte4,
    MSEHasGuidByte2,
    MSEHasMovementFlags2,
    MSEHasGuidByte5,
    MSEHasGuidByte7,
    MSEHasTransportData,
    MSEHasGuidByte6,
    MSEHasSplineElevation,
    MSEHasGuidByte0,
    MSEHasGuidByte3,
    MSEHasPitch,
    MSEHasTimestamp,
    MSEHasFallData,
    MSEMovementFlags2,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte0,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte2,
    MSEHasVehicleId,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte6,
    MSEHasFallDirection,
    MSEMovementFlags,
    MSEGuidByte0,
    MSEGuidByte4,
    MSEGuidByte7,
    MSEGuidByte5,
    MSEGuidByte6,
    MSEGuidByte3,
    MSEGuidByte2,
    MSEGuidByte1,
    MSEFallCosAngle,
    MSEFallSinAngle,
    MSEFallHorizontalSpeed,
    MSEFallVerticalSpeed,
    MSEFallTime,
    MSETransportGuidByte0,
    MSETransportPositionX,
    MSETransportTime,
    MSETransportSeat,
    MSETransportPositionZ,
    MSETransportGuidByte4,
    MSETransportOrientation,
    MSETransportGuidByte2,
    MSETransportGuidByte6,
    MSETransportGuidByte1,
    MSETransportGuidByte3,
    MSETransportPositionY,
    MSETransportVehicleId,
    MSETransportTime2,
    MSETransportGuidByte5,
    MSETransportGuidByte7,
    MSETimestamp,
    MSEPitch,
    MSEOrientation,
    MSESplineElevation,
    MSEEnd,
};

MovementStatusElements const MovementStartTurnRight[] =
{
    MSEPositionX,
    MSEPositionZ,
    MSEPositionY,
    MSEHasGuidByte3,
    MSEHasGuidByte5,
    MSEHasMovementFlags,
    MSEHasSpline,
    MSEHasGuidByte0,
    MSEHasOrientation,
    MSEHasTransportData,
    MSEHasGuidByte7,
    MSEZeroBit,
    MSEHasMovementFlags2,
    MSEHasGuidByte1,
    MSEHasTimestamp,
    MSEHasGuidByte6,
    MSEHasGuidByte2,
    MSEHasGuidByte4,
    MSEHasSplineElevation,
    MSEHasPitch,
    MSEHasFallData,
    MSEHasTransportGuidByte1,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte7,
    MSEHasVehicleId,
    MSEMovementFlags2,
    MSEMovementFlags,
    MSEHasFallDirection,
    MSEGuidByte5,
    MSEGuidByte0,
    MSEGuidByte7,
    MSEGuidByte3,
    MSEGuidByte2,
    MSEGuidByte1,
    MSEGuidByte4,
    MSEGuidByte6,
    MSETransportPositionY,
    MSETransportGuidByte0,
    MSETransportGuidByte4,
    MSETransportGuidByte1,
    MSETransportGuidByte6,
    MSETransportGuidByte2,
    MSETransportSeat,
    MSETransportOrientation,
    MSETransportGuidByte5,
    MSETransportVehicleId,
    MSETransportPositionZ,
    MSETransportPositionX,
    MSETransportTime,
    MSETransportGuidByte7,
    MSETransportGuidByte3,
    MSETransportTime2,
    MSEFallHorizontalSpeed,
    MSEFallCosAngle,
    MSEFallSinAngle,
    MSEFallTime,
    MSEFallVerticalSpeed,
    MSEPitch,
    MSEOrientation,
    MSESplineElevation,
    MSETimestamp,
    MSEEnd,
};

MovementStatusElements const MovementStop[] =
{
    MSEPositionX,
    MSEPositionY,
    MSEPositionZ,
    MSEHasGuidByte3,
    MSEHasGuidByte6,
    MSEHasSplineElevation,
    MSEHasSpline,
    MSEHasOrientation,
    MSEHasGuidByte7,
    MSEHasMovementFlags,
    MSEHasGuidByte5,
    MSEHasFallData,
    MSEHasMovementFlags2,
    MSEHasTransportData,
    MSEHasTimestamp,
    MSEHasGuidByte4,
    MSEHasGuidByte1,
    MSEZeroBit,
    MSEHasGuidByte2,
    MSEHasGuidByte0,
    MSEHasPitch,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte5,
    MSEHasTransportTime2,
    MSEHasVehicleId,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte2,
    MSEMovementFlags,
    MSEMovementFlags2,
    MSEHasFallDirection,
    MSEGuidByte6,
    MSEGuidByte3,
    MSEGuidByte0,
    MSEGuidByte4,
    MSEGuidByte2,
    MSEGuidByte1,
    MSEGuidByte5,
    MSEGuidByte7,
    MSETransportGuidByte4,
    MSETransportGuidByte7,
    MSETransportTime,
    MSETransportSeat,
    MSETransportPositionZ,
    MSETransportVehicleId,
    MSETransportGuidByte2,
    MSETransportGuidByte0,
    MSETransportPositionY,
    MSETransportGuidByte1,
    MSETransportGuidByte3,
    MSETransportTime2,
    MSETransportPositionX,
    MSETransportOrientation,
    MSETransportGuidByte5,
    MSETransportGuidByte6,
    MSETimestamp,
    MSEOrientation,
    MSEPitch,
    MSESplineElevation,
    MSEFallSinAngle,
    MSEFallCosAngle,
    MSEFallHorizontalSpeed,
    MSEFallVerticalSpeed,
    MSEFallTime,
    MSEEnd,
};

MovementStatusElements const MovementStopStrafe[] =
{
    MSEPositionY,
    MSEPositionZ,
    MSEPositionX,
    MSEHasPitch,
    MSEHasTimestamp,
    MSEHasGuidByte2,
    MSEHasFallData,
    MSEHasGuidByte7,
    MSEHasSplineElevation,
    MSEHasGuidByte3,
    MSEHasOrientation,
    MSEHasMovementFlags2,
    MSEHasTransportData,
    MSEHasMovementFlags,
    MSEHasSpline,
    MSEHasGuidByte0,
    MSEZeroBit,
    MSEHasGuidByte6,
    MSEHasGuidByte5,
    MSEHasGuidByte1,
    MSEHasGuidByte4,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte5,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte3,
    MSEHasVehicleId,
    MSEMovementFlags,
    MSEHasFallDirection,
    MSEMovementFlags2,
    MSEGuidByte2,
    MSEGuidByte7,
    MSEGuidByte3,
    MSEGuidByte4,
    MSEGuidByte5,
    MSEGuidByte6,
    MSEGuidByte1,
    MSEGuidByte0,
    MSETransportSeat,
    MSETransportGuidByte6,
    MSETransportPositionZ,
    MSETransportVehicleId,
    MSETransportGuidByte1,
    MSETransportGuidByte3,
    MSETransportGuidByte2,
    MSETransportGuidByte4,
    MSETransportGuidByte5,
    MSETransportTime,
    MSETransportOrientation,
    MSETransportPositionX,
    MSETransportGuidByte0,
    MSETransportPositionY,
    MSETransportTime2,
    MSETransportGuidByte7,
    MSEFallSinAngle,
    MSEFallHorizontalSpeed,
    MSEFallCosAngle,
    MSEFallTime,
    MSEFallVerticalSpeed,
    MSESplineElevation,
    MSEOrientation,
    MSEPitch,
    MSETimestamp,
    MSEEnd,
};

MovementStatusElements const MovementStopTurn[] =
{
    MSEPositionX,
    MSEPositionZ,
    MSEPositionY,
    MSEHasGuidByte5,
    MSEHasGuidByte4,
    MSEHasFallData,
    MSEZeroBit,
    MSEHasGuidByte1,
    MSEHasGuidByte0,
    MSEHasSpline,
    MSEHasMovementFlags,
    MSEHasGuidByte2,
    MSEHasGuidByte6,
    MSEHasPitch,
    MSEHasTransportData,
    MSEHasGuidByte3,
    MSEHasSplineElevation,
    MSEHasTimestamp,
    MSEHasMovementFlags2,
    MSEHasOrientation,
    MSEHasGuidByte7,
    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte7,
    MSEHasVehicleId,
    MSEHasTransportGuidByte4,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte1,
    MSEHasFallDirection,
    MSEMovementFlags,
    MSEMovementFlags2,
    MSEGuidByte3,
    MSEGuidByte2,
    MSEGuidByte6,
    MSEGuidByte4,
    MSEGuidByte0,
    MSEGuidByte7,
    MSEGuidByte1,
    MSEGuidByte5,
    MSESplineElevation,
    MSETransportPositionX,
    MSETransportGuidByte5,
    MSETransportSeat,
    MSETransportGuidByte2,
    MSETransportGuidByte3,
    MSETransportOrientation,
    MSETransportTime2,
    MSETransportVehicleId,
    MSETransportGuidByte7,
    MSETransportGuidByte1,
    MSETransportGuidByte0,
    MSETransportGuidByte4,
    MSETransportPositionY,
    MSETransportPositionZ,
    MSETransportTime,
    MSETransportGuidByte6,
    MSEFallTime,
    MSEFallHorizontalSpeed,
    MSEFallSinAngle,
    MSEFallCosAngle,
    MSEFallVerticalSpeed,
    MSETimestamp,
    MSEPitch,
    MSEOrientation,
    MSEEnd,
};

MovementStatusElements const MovementStartAscend[] =
{
    MSEPositionX,
    MSEPositionY,
    MSEPositionZ,
    MSEHasGuidByte0,
    MSEHasGuidByte1,
    MSEHasGuidByte7,
    MSEZeroBit,
    MSEHasGuidByte5,
    MSEHasTransportData,
    MSEHasGuidByte2,
    MSEHasSplineElevation,
    MSEHasFallData,
    MSEHasSpline,
    MSEHasGuidByte3,
    MSEHasMovementFlags2,
    MSEHasGuidByte6,
    MSEHasMovementFlags,
    MSEHasPitch,
    MSEHasTimestamp,
    MSEHasOrientation,
    MSEHasGuidByte4,
    MSEMovementFlags,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte2,
    MSEHasVehicleId,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte4,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte7,
    MSEMovementFlags2,
    MSEHasFallDirection,
    MSEGuidByte6,
    MSEGuidByte3,
    MSEGuidByte1,
    MSEGuidByte4,
    MSEGuidByte2,
    MSEGuidByte0,
    MSEGuidByte5,
    MSEGuidByte7,
    MSETransportGuidByte3,
    MSETransportGuidByte5,
    MSETransportGuidByte4,
    MSETransportSeat,
    MSETransportGuidByte2,
    MSETransportOrientation,
    MSETransportPositionY,
    MSETransportGuidByte7,
    MSETransportTime2,
    MSETransportPositionZ,
    MSETransportVehicleId,
    MSETransportGuidByte6,
    MSETransportTime,
    MSETransportGuidByte0,
    MSETransportGuidByte1,
    MSETransportPositionX,
    MSEFallSinAngle,
    MSEFallCosAngle,
    MSEFallHorizontalSpeed,
    MSEFallTime,
    MSEFallVerticalSpeed,
    MSEOrientation,
    MSEPitch,
    MSETimestamp,
    MSESplineElevation,
    MSEEnd,
};

MovementStatusElements const MovementStartDescend[] =
{
    MSEPositionY,
    MSEPositionZ,
    MSEPositionX,
    MSEHasGuidByte0,
    MSEHasPitch,
    MSEHasFallData,
    MSEHasGuidByte4,
    MSEHasOrientation,
    MSEHasTimestamp,
    MSEHasMovementFlags2,
    MSEHasMovementFlags,
    MSEHasGuidByte6,
    MSEZeroBit,
    MSEHasGuidByte1,
    MSEHasTransportData,
    MSEHasSpline,
    MSEHasSplineElevation,
    MSEHasGuidByte5,
    MSEHasGuidByte3,
    MSEHasGuidByte7,
    MSEHasGuidByte2,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte2,
    MSEHasVehicleId,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte6,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte5,
    MSEMovementFlags2,
    MSEMovementFlags,
    MSEHasFallDirection,
    MSEGuidByte2,
    MSEGuidByte7,
    MSEGuidByte6,
    MSEGuidByte0,
    MSEGuidByte1,
    MSEGuidByte5,
    MSEGuidByte4,
    MSEGuidByte3,
    MSEPitch,
    MSETransportPositionZ,
    MSETransportSeat,
    MSETransportVehicleId,
    MSETransportGuidByte6,
    MSETransportTime2,
    MSETransportGuidByte1,
    MSETransportTime,
    MSETransportGuidByte4,
    MSETransportPositionY,
    MSETransportPositionX,
    MSETransportGuidByte7,
    MSETransportGuidByte3,
    MSETransportGuidByte5,
    MSETransportGuidByte2,
    MSETransportOrientation,
    MSETransportGuidByte0,
    MSEFallTime,
    MSEFallCosAngle,
    MSEFallSinAngle,
    MSEFallHorizontalSpeed,
    MSEFallVerticalSpeed,
    MSETimestamp,
    MSEOrientation,
    MSESplineElevation,
    MSEEnd,
};

MovementStatusElements const MovementStartSwim[] =
{
    MSEPositionZ,
    MSEPositionX,
    MSEPositionY,
    MSEHasGuidByte3,
    MSEHasSplineElevation,
    MSEHasGuidByte4,
    MSEHasGuidByte7,
    MSEZeroBit,
    MSEHasPitch,
    MSEHasGuidByte0,
    MSEHasOrientation,
    MSEHasMovementFlags,
    MSEHasFallData,
    MSEHasGuidByte5,
    MSEHasTransportData,
    MSEHasMovementFlags2,
    MSEHasTimestamp,
    MSEHasGuidByte6,
    MSEHasGuidByte1,
    MSEHasSpline,
    MSEHasGuidByte2,
    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte0,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte1,
    MSEHasVehicleId,
    MSEMovementFlags,
    MSEHasFallDirection,
    MSEMovementFlags2,
    MSEGuidByte0,
    MSEGuidByte2,
    MSEGuidByte1,
    MSEGuidByte5,
    MSEGuidByte4,
    MSEGuidByte6,
    MSEGuidByte3,
    MSEGuidByte7,
    MSEPitch,
    MSETransportTime2,
    MSETransportGuidByte2,
    MSETransportPositionY,
    MSETransportGuidByte3,
    MSETransportTime,
    MSETransportPositionX,
    MSETransportOrientation,
    MSETransportVehicleId,
    MSETransportGuidByte6,
    MSETransportGuidByte5,
    MSETransportGuidByte4,
    MSETransportPositionZ,
    MSETransportGuidByte1,
    MSETransportGuidByte7,
    MSETransportGuidByte0,
    MSETransportSeat,
    MSEFallSinAngle,
    MSEFallHorizontalSpeed,
    MSEFallCosAngle,
    MSEFallVerticalSpeed,
    MSEFallTime,
    MSEOrientation,
    MSETimestamp,
    MSESplineElevation,
    MSEEnd,
};

MovementStatusElements const MovementStopSwim[] =
{
    MSEPositionX,
    MSEPositionY,
    MSEPositionZ,
    MSEHasSpline,
    MSEHasPitch,
    MSEHasGuidByte5,
    MSEHasGuidByte3,
    MSEHasGuidByte7,
    MSEHasSplineElevation,
    MSEHasMovementFlags,
    MSEHasGuidByte4,
    MSEHasMovementFlags2,
    MSEHasGuidByte2,
    MSEHasGuidByte6,
    MSEHasTransportData,
    MSEHasOrientation,
    MSEZeroBit,
    MSEHasTimestamp,
    MSEHasGuidByte1,
    MSEHasGuidByte0,
    MSEHasFallData,
    MSEHasVehicleId,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte0,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte5,
    MSEMovementFlags,
    MSEMovementFlags2,
    MSEHasFallDirection,
    MSEGuidByte0,
    MSEGuidByte4,
    MSEGuidByte3,
    MSEGuidByte6,
    MSEGuidByte7,
    MSEGuidByte1,
    MSEGuidByte5,
    MSEGuidByte2,
    MSETransportVehicleId,
    MSETransportGuidByte4,
    MSETransportTime,
    MSETransportPositionZ,
    MSETransportSeat,
    MSETransportGuidByte3,
    MSETransportGuidByte2,
    MSETransportPositionY,
    MSETransportGuidByte7,
    MSETransportGuidByte1,
    MSETransportGuidByte6,
    MSETransportGuidByte5,
    MSETransportTime2,
    MSETransportPositionX,
    MSETransportGuidByte0,
    MSETransportOrientation,
    MSEFallVerticalSpeed,
    MSEFallSinAngle,
    MSEFallHorizontalSpeed,
    MSEFallCosAngle,
    MSEFallTime,
    MSETimestamp,
    MSEPitch,
    MSEOrientation,
    MSESplineElevation,
    MSEEnd,
};

MovementStatusElements const MovementStopAscend[] =
{
    MSEPositionZ,
    MSEPositionY,
    MSEPositionX,
    MSEHasGuidByte3,
    MSEHasGuidByte2,
    MSEHasFallData,
    MSEHasGuidByte7,
    MSEHasOrientation,
    MSEHasPitch,
    MSEHasSpline,
    MSEZeroBit,
    MSEHasGuidByte1,
    MSEHasGuidByte4,
    MSEHasMovementFlags,
    MSEHasGuidByte0,
    MSEHasGuidByte6,
    MSEHasSplineElevation,
    MSEHasTransportData,
    MSEHasMovementFlags2,
    MSEHasTimestamp,
    MSEHasGuidByte5,
    MSEHasTransportTime2,
    MSEHasVehicleId,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte0,
    MSEMovementFlags2,
    MSEMovementFlags,
    MSEHasFallDirection,
    MSEGuidByte7,
    MSEGuidByte5,
    MSEGuidByte4,
    MSEGuidByte3,
    MSEGuidByte2,
    MSEGuidByte1,
    MSEGuidByte0,
    MSEGuidByte6,
    MSETransportGuidByte5,
    MSETransportPositionY,
    MSETransportGuidByte7,
    MSETransportGuidByte2,
    MSETransportGuidByte6,
    MSETransportTime2,
    MSETransportVehicleId,
    MSETransportOrientation,
    MSETransportGuidByte3,
    MSETransportGuidByte4,
    MSETransportSeat,
    MSETransportGuidByte1,
    MSETransportTime,
    MSETransportGuidByte0,
    MSETransportPositionX,
    MSETransportPositionZ,
    MSEFallTime,
    MSEFallVerticalSpeed,
    MSEFallSinAngle,
    MSEFallCosAngle,
    MSEFallHorizontalSpeed,
    MSEPitch,
    MSESplineElevation,
    MSETimestamp,
    MSEOrientation,
    MSEEnd,
};

MovementStatusElements const MovementStopPitch[] =
{
    MSEPositionX,
    MSEPositionZ,
    MSEPositionY,
    MSEHasGuidByte0,
    MSEHasGuidByte5,
    MSEHasGuidByte3,
    MSEHasFallData,
    MSEHasGuidByte2,
    MSEHasGuidByte4,
    MSEHasGuidByte7,
    MSEHasPitch,
    MSEHasSpline,
    MSEHasOrientation,
    MSEZeroBit,
    MSEHasMovementFlags2,
    MSEHasSplineElevation,
    MSEHasGuidByte6,
    MSEHasGuidByte1,
    MSEHasTimestamp,
    MSEHasTransportData,
    MSEHasMovementFlags,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte2,
    MSEHasVehicleId,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte3,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte1,
    MSEHasFallDirection,
    MSEMovementFlags2,
    MSEMovementFlags,
    MSEGuidByte1,
    MSEGuidByte7,
    MSEGuidByte0,
    MSEGuidByte6,
    MSEGuidByte4,
    MSEGuidByte3,
    MSEGuidByte5,
    MSEGuidByte2,
    MSETimestamp,
    MSEFallHorizontalSpeed,
    MSEFallCosAngle,
    MSEFallSinAngle,
    MSEFallVerticalSpeed,
    MSEFallTime,
    MSETransportGuidByte5,
    MSETransportGuidByte2,
    MSETransportTime2,
    MSETransportPositionX,
    MSETransportOrientation,
    MSETransportGuidByte6,
    MSETransportGuidByte3,
    MSETransportGuidByte1,
    MSETransportPositionZ,
    MSETransportVehicleId,
    MSETransportGuidByte0,
    MSETransportGuidByte4,
    MSETransportTime,
    MSETransportPositionY,
    MSETransportSeat,
    MSETransportGuidByte7,
    MSESplineElevation,
    MSEOrientation,
    MSEPitch,
    MSEEnd,
};

MovementStatusElements const MovementStartPitchDown[] =
{
    MSEPositionX,
    MSEPositionZ,
    MSEPositionY,
    MSEHasMovementFlags,
    MSEHasGuidByte7,
    MSEHasGuidByte6,
    MSEHasPitch,
    MSEZeroBit,
    MSEHasGuidByte1,
    MSEHasGuidByte4,
    MSEHasTimestamp,
    MSEHasSplineElevation,
    MSEHasMovementFlags2,
    MSEHasTransportData,
    MSEHasGuidByte0,
    MSEHasGuidByte5,
    MSEHasGuidByte3,
    MSEHasSpline,
    MSEHasOrientation,
    MSEHasFallData,
    MSEHasGuidByte2,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte5,
    MSEHasVehicleId,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte6,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte2,
    MSEMovementFlags2,
    MSEHasFallDirection,
    MSEMovementFlags,
    MSEGuidByte3,
    MSEGuidByte7,
    MSEGuidByte0,
    MSEGuidByte5,
    MSEGuidByte2,
    MSEGuidByte6,
    MSEGuidByte4,
    MSEGuidByte1,
    MSETransportVehicleId,
    MSETransportGuidByte3,
    MSETransportTime2,
    MSETransportGuidByte5,
    MSETransportGuidByte1,
    MSETransportPositionY,
    MSETransportGuidByte6,
    MSETransportGuidByte4,
    MSETransportTime,
    MSETransportPositionZ,
    MSETransportPositionX,
    MSETransportGuidByte0,
    MSETransportSeat,
    MSETransportGuidByte2,
    MSETransportGuidByte7,
    MSETransportOrientation,
    MSEFallCosAngle,
    MSEFallHorizontalSpeed,
    MSEFallSinAngle,
    MSEFallVerticalSpeed,
    MSEFallTime,
    MSEPitch,
    MSEOrientation,
    MSESplineElevation,
    MSETimestamp,
    MSEEnd,
};

MovementStatusElements const MovementStartPitchUp[] =
{
    MSEPositionZ,
    MSEPositionY,
    MSEPositionX,
    MSEHasGuidByte4,
    MSEHasMovementFlags,
    MSEHasMovementFlags2,
    MSEHasSpline,
    MSEHasGuidByte2,
    MSEHasGuidByte6,
    MSEHasGuidByte3,
    MSEZeroBit,
    MSEHasSplineElevation,
    MSEHasFallData,
    MSEHasGuidByte0,
    MSEHasTransportData,
    MSEHasGuidByte1,
    MSEHasGuidByte5,
    MSEHasPitch,
    MSEHasTimestamp,
    MSEHasOrientation,
    MSEHasGuidByte7,
    MSEMovementFlags2,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte1,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte4,
    MSEHasVehicleId,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte2,
    MSEMovementFlags,
    MSEHasFallDirection,
    MSEGuidByte0,
    MSEGuidByte3,
    MSEGuidByte4,
    MSEGuidByte6,
    MSEGuidByte7,
    MSEGuidByte1,
    MSEGuidByte5,
    MSEGuidByte2,
    MSETransportPositionX,
    MSETransportGuidByte1,
    MSETransportGuidByte3,
    MSETransportGuidByte2,
    MSETransportGuidByte0,
    MSETransportTime,
    MSETransportPositionZ,
    MSETransportOrientation,
    MSETransportGuidByte7,
    MSETransportTime2,
    MSETransportSeat,
    MSETransportGuidByte6,
    MSETransportGuidByte5,
    MSETransportVehicleId,
    MSETransportPositionY,
    MSETransportGuidByte4,
    MSEFallTime,
    MSEFallSinAngle,
    MSEFallCosAngle,
    MSEFallHorizontalSpeed,
    MSEFallVerticalSpeed,
    MSEOrientation,
    MSESplineElevation,
    MSEPitch,
    MSETimestamp,
    MSEEnd,
};

MovementStatusElements const MoveChngTransport[]=
{
    MSEPositionY,
    MSEPositionX,
    MSEPositionZ,
    MSEHasGuidByte4,
    MSEHasGuidByte0,
    MSEHasGuidByte2,
    MSEHasTransportData,
    MSEHasSpline,
    MSEHasOrientation,
    MSEHasGuidByte6,
    MSEHasTimestamp,
    MSEHasGuidByte5,
    MSEHasGuidByte7,
    MSEHasPitch,
    MSEZeroBit,
    MSEHasGuidByte3,
    MSEHasSplineElevation,
    MSEHasGuidByte1,
    MSEHasFallData,
    MSEHasMovementFlags,
    MSEHasMovementFlags2,
    MSEHasTransportGuidByte3,
    MSEHasVehicleId,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte2,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte5,
    MSEMovementFlags,
    MSEMovementFlags2,
    MSEHasFallDirection,
    MSEGuidByte7,
    MSEGuidByte5,
    MSEGuidByte1,
    MSEGuidByte2,
    MSEGuidByte6,
    MSEGuidByte4,
    MSEGuidByte0,
    MSEGuidByte3,
    MSETransportPositionY,
    MSETransportSeat,
    MSETransportGuidByte1,
    MSETransportGuidByte0,
    MSETransportGuidByte2,
    MSETransportGuidByte3,
    MSETransportGuidByte6,
    MSETransportPositionZ,
    MSETransportPositionX,
    MSETransportVehicleId,
    MSETransportTime,
    MSETransportGuidByte7,
    MSETransportGuidByte5,
    MSETransportGuidByte4,
    MSETransportOrientation,
    MSETransportTime2,
    MSEFallTime,
    MSEFallHorizontalSpeed,
    MSEFallSinAngle,
    MSEFallCosAngle,
    MSEFallVerticalSpeed,
    MSEOrientation,
    MSEPitch,
    MSESplineElevation,
    MSETimestamp,
    MSEEnd,
};

MovementStatusElements const MoveSplineDone[] =
{
    MSEPositionY,
    MSEPositionX,
    MSEPositionZ,
    MSEHasGuidByte6,
    MSEHasOrientation,
    MSEHasFallData,
    MSEHasTimestamp,
    MSEHasGuidByte2,
    MSEHasSplineElevation,
    MSEHasGuidByte4,
    MSEHasTransportData,
    MSEHasGuidByte3,
    MSEHasMovementFlags,
    MSEHasGuidByte0,
    MSEZeroBit,
    MSEHasGuidByte1,
    MSEHasGuidByte5,
    MSEHasPitch,
    MSEHasSpline,
    MSEHasMovementFlags2,
    MSEHasGuidByte7,

    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte6,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte2,
    MSEHasVehicleId,
    MSEHasTransportGuidByte0,

    MSEHasFallDirection,
    MSEMovementFlags2,
    MSEMovementFlags,

    MSEGuidByte7,
    MSEGuidByte4,
    MSEGuidByte5,
    MSEGuidByte6,
    MSEGuidByte0,
    MSEGuidByte1,
    MSEGuidByte2,
    MSEGuidByte3,

    MSEFallVerticalSpeed,
    MSEFallCosAngle,
    MSEFallSinAngle,
    MSEFallHorizontalSpeed,
    MSEFallTime,

    MSEPitch,
    MSEOrientation,

    MSETransportGuidByte1,
    MSETransportVehicleId,
    MSETransportGuidByte7,
    MSETransportTime,
    MSETransportPositionY,
    MSETransportPositionX,
    MSETransportPositionZ,
    MSETransportSeat,
    MSETransportOrientation,
    MSETransportGuidByte0,
    MSETransportTime2,
    MSETransportGuidByte2,
    MSETransportGuidByte3,
    MSETransportGuidByte5,
    MSETransportGuidByte6,
    MSETransportGuidByte4,

    MSETimestamp,
    MSESplineElevation,
    MSEEnd,
};

MovementStatusElements const MoveNotActiveMover[] =
{
    MSEPositionZ,
    MSEPositionX,
    MSEPositionY,
    MSEHasMovementFlags2,
    MSEHasTransportData,
    MSEHasGuidByte6,
    MSEHasSplineElevation,
    MSEHasGuidByte3,
    MSEZeroBit,
    MSEHasTimestamp,
    MSEHasGuidByte0,
    MSEHasOrientation,
    MSEHasGuidByte5,
    MSEHasPitch,
    MSEHasGuidByte1,
    MSEHasGuidByte4,
    MSEHasGuidByte7,
    MSEHasSpline,
    MSEHasGuidByte2,
    MSEHasFallData,
    MSEHasMovementFlags,

    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte2,
    MSEHasVehicleId,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte7,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte3,

    MSEHasFallDirection,
    MSEMovementFlags,
    MSEMovementFlags2,

    MSEGuidByte1,
    MSEGuidByte0,
    MSEGuidByte4,
    MSEGuidByte2,
    MSEGuidByte7,
    MSEGuidByte5,
    MSEGuidByte6,
    MSEGuidByte3,

    MSEFallVerticalSpeed,
    MSEFallSinAngle,
    MSEFallCosAngle,
    MSEFallHorizontalSpeed,
    MSEFallTime,

    MSETransportVehicleId,
    MSETransportGuidByte1,
    MSETransportTime2,
    MSETransportOrientation,
    MSETransportGuidByte0,
    MSETransportSeat,
    MSETransportGuidByte4,
    MSETransportGuidByte6,
    MSETransportGuidByte3,
    MSETransportGuidByte5,
    MSETransportPositionY,
    MSETransportPositionX,
    MSETransportGuidByte2,
    MSETransportPositionZ,
    MSETransportGuidByte7,
    MSETransportTime,

    MSETimestamp,
    MSESplineElevation,
    MSEPitch,
    MSEOrientation,

    MSEEnd,
};

MovementStatusElements const DismissControlledVehicle[] =
{
    MSEPositionY,
    MSEPositionZ,
    MSEPositionX,
    MSEHasSplineElevation,
    MSEHasFallData,
    MSEHasTransportData,
    MSEHasGuidByte4,
    MSEHasGuidByte7,
    MSEHasMovementFlags2,
    MSEHasGuidByte2,
    MSEHasOrientation,
    MSEHasGuidByte0,
    MSEHasGuidByte6,
    MSEHasPitch,
    MSEHasTimestamp,
    MSEHasGuidByte1,
    MSEZeroBit,
    MSEHasSpline,
    MSEHasGuidByte3,
    MSEHasMovementFlags,
    MSEHasGuidByte5,

    MSEHasTransportGuidByte5,
    MSEHasVehicleId,
    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte6,
    MSEHasTransportTime2,

    MSEMovementFlags2,
    MSEHasFallDirection,
    MSEMovementFlags,

    MSEGuidByte6,
    MSEGuidByte3,
    MSEGuidByte1,
    MSEGuidByte5,
    MSEGuidByte2,
    MSEGuidByte4,
    MSEGuidByte7,
    MSEGuidByte0,

    MSETimestamp,

    MSETransportVehicleId,
    MSETransportGuidByte4,
    MSETransportGuidByte7,
    MSETransportTime2,
    MSETransportGuidByte6,
    MSETransportTime,
    MSETransportPositionZ,
    MSETransportGuidByte0,
    MSETransportPositionX,
    MSETransportGuidByte3,
    MSETransportSeat,
    MSETransportPositionY,
    MSETransportOrientation,
    MSETransportGuidByte1,
    MSETransportGuidByte5,
    MSETransportGuidByte2,

    MSEFallTime,
    MSEFallHorizontalSpeed,
    MSEFallCosAngle,
    MSEFallSinAngle,
    MSEFallVerticalSpeed,

    MSEOrientation,
    MSESplineElevation,
    MSEPitch,
    MSEEnd,
};

MovementStatusElements const MovementSetRunMode[] =
{
    MSEPositionY,
    MSEPositionX,
    MSEPositionZ,
    MSEHasTimestamp,
    MSEHasMovementFlags2,
    MSEHasGuidByte1,
    MSEHasSpline,
    MSEHasMovementFlags,
    MSEHasGuidByte7,
    MSEHasTransportData,
    MSEZeroBit,
    MSEHasGuidByte0,
    MSEHasGuidByte3,
    MSEHasSplineElevation,
    MSEHasGuidByte5,
    MSEHasPitch,
    MSEHasGuidByte6,
    MSEHasGuidByte4,
    MSEHasFallData,
    MSEHasOrientation,
    MSEHasGuidByte2,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte4,
    MSEHasVehicleId,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte1,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte2,
    MSEHasFallDirection,
    MSEMovementFlags2,
    MSEMovementFlags,
    MSEGuidByte3,
    MSEGuidByte6,
    MSEGuidByte0,
    MSEGuidByte7,
    MSEGuidByte4,
    MSEGuidByte1,
    MSEGuidByte5,
    MSEGuidByte2,
    MSEPitch,
    MSETransportTime2,
    MSETransportGuidByte3,
    MSETransportPositionX,
    MSETransportSeat,
    MSETransportGuidByte5,
    MSETransportGuidByte1,
    MSETransportPositionZ,
    MSETransportGuidByte2,
    MSETransportGuidByte7,
    MSETransportOrientation,
    MSETransportGuidByte4,
    MSETransportTime,
    MSETransportVehicleId,
    MSETransportGuidByte0,
    MSETransportPositionY,
    MSETransportGuidByte6,
    MSEFallSinAngle,
    MSEFallHorizontalSpeed,
    MSEFallCosAngle,
    MSEFallTime,
    MSEFallVerticalSpeed,
    MSESplineElevation,
    MSETimestamp,
    MSEOrientation,
    MSEEnd
};

MovementStatusElements const MovementSetWalkMode[] =
{
    MSEPositionY,
    MSEPositionX,
    MSEPositionZ,
    MSEHasGuidByte6,
    MSEHasSpline,
    MSEHasTimestamp,
    MSEHasGuidByte0,
    MSEHasGuidByte1,
    MSEHasMovementFlags,
    MSEHasPitch,
    MSEHasGuidByte7,
    MSEHasSplineElevation,
    MSEHasGuidByte4,
    MSEHasOrientation,
    MSEHasTransportData,
    MSEHasGuidByte2,
    MSEHasGuidByte5,
    MSEHasGuidByte3,
    MSEZeroBit,
    MSEHasMovementFlags2,
    MSEHasFallData,
    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte3,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte5,
    MSEHasVehicleId,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte7,
    MSEHasFallDirection,
    MSEMovementFlags,
    MSEMovementFlags2,
    MSEGuidByte5,
    MSEGuidByte6,
    MSEGuidByte4,
    MSEGuidByte7,
    MSEGuidByte3,
    MSEGuidByte0,
    MSEGuidByte2,
    MSEGuidByte1,
    MSETransportGuidByte2,
    MSETransportGuidByte5,
    MSETransportSeat,
    MSETransportPositionZ,
    MSETransportGuidByte3,
    MSETransportGuidByte6,
    MSETransportGuidByte0,
    MSETransportTime,
    MSETransportGuidByte4,
    MSETransportTime2,
    MSETransportOrientation,
    MSETransportPositionX,
    MSETransportVehicleId,
    MSETransportGuidByte7,
    MSETransportPositionY,
    MSETransportGuidByte1,
    MSEFallCosAngle,
    MSEFallHorizontalSpeed,
    MSEFallSinAngle,
    MSEFallVerticalSpeed,
    MSEFallTime,
    MSESplineElevation,
    MSEPitch,
    MSETimestamp,
    MSEOrientation,
    MSEEnd
};

MovementStatusElements const MovementSetCanFly[] =
{
    MSEPositionZ,
    MSEPositionX,
    MSEPositionY,
    MSEHasTransportData,
    MSEHasGuidByte1,
    MSEHasGuidByte6,
    MSEHasGuidByte4,
    MSEHasGuidByte2,
    MSEHasFallData,
    MSEHasGuidByte0,
    MSEHasMovementFlags,
    MSEHasGuidByte3,
    MSEHasMovementFlags2,
    MSEHasGuidByte5,
    MSEHasTimestamp,
    MSEHasSplineElevation,
    MSEHasSpline,
    MSEHasOrientation,
    MSEHasGuidByte7,
    MSEZeroBit,
    MSEHasPitch,
    MSEHasTransportGuidByte3,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte4,
    MSEHasVehicleId,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte5,
    MSEMovementFlags2,
    MSEHasFallDirection,
    MSEMovementFlags,
    MSEGuidByte2,
    MSEGuidByte0,
    MSEGuidByte4,
    MSEGuidByte7,
    MSEGuidByte5,
    MSEGuidByte1,
    MSEGuidByte3,
    MSEGuidByte6,
    MSETransportPositionZ,
    MSETransportGuidByte3,
    MSETransportGuidByte5,
    MSETransportGuidByte4,
    MSETransportSeat,
    MSETransportPositionX,
    MSETransportGuidByte2,
    MSETransportTime2,
    MSETransportPositionY,
    MSETransportGuidByte1,
    MSETransportTime,
    MSETransportGuidByte7,
    MSETransportGuidByte0,
    MSETransportOrientation,
    MSETransportGuidByte6,
    MSETransportVehicleId,
    MSESplineElevation,
    MSEFallSinAngle,
    MSEFallCosAngle,
    MSEFallHorizontalSpeed,
    MSEFallVerticalSpeed,
    MSEFallTime,
    MSEPitch,
    MSETimestamp,
    MSEOrientation,
    MSEEnd,
};

MovementStatusElements const MovementSetCanTransitionBetweenSwimAndFlyAck[] =
{
    MSEPositionZ,
    MSEPositionY,
    MSECounter,
    MSEPositionX,
    MSEHasGuidByte3,
    MSEHasOrientation,
    MSEHasTransportData,
    MSEHasMovementFlags,
    MSEHasMovementFlags2,
    MSEHasSplineElevation,
    MSEHasTimestamp,
    MSEHasSpline,
    MSEZeroBit,
    MSEHasFallData,
    MSEHasGuidByte5,
    MSEHasGuidByte0,
    MSEHasGuidByte1,
    MSEHasGuidByte4,
    MSEHasGuidByte6,
    MSEHasGuidByte2,
    MSEHasPitch,
    MSEHasGuidByte7,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte2,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte5,
    MSEHasVehicleId,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte1,
    MSEMovementFlags2,
    MSEHasFallDirection,
    MSEMovementFlags,
    MSEGuidByte3,
    MSEGuidByte2,
    MSEGuidByte0,
    MSEGuidByte4,
    MSEGuidByte1,
    MSEGuidByte5,
    MSEGuidByte7,
    MSEGuidByte6,
    MSEFallTime,
    MSEFallHorizontalSpeed,
    MSEFallCosAngle,
    MSEFallSinAngle,
    MSEFallVerticalSpeed,
    MSETransportPositionY,
    MSETransportPositionZ,
    MSETransportGuidByte5,
    MSETransportGuidByte1,
    MSETransportGuidByte4,
    MSETransportTime,
    MSETransportSeat,
    MSETransportGuidByte3,
    MSETransportGuidByte0,
    MSETransportGuidByte2,
    MSETransportGuidByte7,
    MSETransportPositionX,
    MSETransportTime2,
    MSETransportGuidByte6,
    MSETransportOrientation,
    MSETransportVehicleId,
    MSEPitch,
    MSEOrientation,
    MSETimestamp,
    MSESplineElevation,
    MSEEnd,
};

MovementStatusElements const MovementUpdateSwimSpeed[] =
{
    MSEHasMovementFlags,
    MSEHasGuidByte2,
    MSEHasSpline,
    MSEHasTimestamp,
    MSEMovementFlags,
    MSEHasFallData,
    MSEHasGuidByte3,
    MSEHasTransportData,
    MSEZeroBit, // height_change_failed
    MSEHasGuidByte7,
    MSEHasFallDirection,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte3,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte2,
    MSEHasVehicleId,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte7,
    MSEHasMovementFlags2,
    MSEHasGuidByte6,
    MSEHasSplineElevation,
    MSEHasGuidByte0,
    MSEHasGuidByte4,
    MSEHasGuidByte5,
    MSEHasOrientation,
    MSEHasPitch,
    MSEMovementFlags2,
    MSEHasGuidByte1,
    MSEFlushBits,
    MSETransportGuidByte2,
    MSETransportPositionX,
    MSETransportVehicleId,
    MSETransportTime2,
    MSETransportGuidByte6,
    MSETransportOrientation,
    MSETransportGuidByte0,
    MSETransportGuidByte4,
    MSETransportPositionY,
    MSETransportTime,
    MSETransportGuidByte1,
    MSETransportGuidByte7,
    MSETransportPositionZ,
    MSETransportSeat,
    MSETransportGuidByte3,
    MSETransportGuidByte5,
    MSEPositionX,
    MSEFallCosAngle,
    MSEFallHorizontalSpeed,
    MSEFallSinAngle,
    MSEFallTime,
    MSEFallVerticalSpeed,
    MSEGuidByte7,
    MSETimestamp,
    MSEPositionY,
    MSESplineElevation,
    MSEPositionZ,
    MSEExtraElement,
    MSEGuidByte4,
    MSEOrientation,
    MSEGuidByte2,
    MSEGuidByte3,
    MSEGuidByte0,
    MSEGuidByte6,
    MSEGuidByte1,
    MSEGuidByte5,
    MSEPitch,
    MSEEnd,
};

MovementStatusElements const MovementUpdateRunSpeed[] =
{
    MSEPositionZ,
    MSEPositionX,
    MSEPositionY,
    MSEExtraElement,
    MSEHasGuidByte6,
    MSEHasMovementFlags2,
    MSEHasPitch,
    MSEHasGuidByte2,
    MSEHasGuidByte5,
    MSEHasSplineElevation,
    MSEHasSpline,
    MSEHasMovementFlags,
    MSEHasTimestamp,
    MSEHasGuidByte1,
    MSEMovementFlags2,
    MSEHasGuidByte3,
    MSEMovementFlags,
    MSEHasGuidByte7,
    MSEHasGuidByte0,
    MSEHasOrientation,
    MSEHasTransportData,
    MSEHasTransportGuidByte5,
    MSEHasTransportTime2,
    MSEHasVehicleId,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte0,
    MSEHasFallData,
    MSEHasFallDirection,
    MSEHasGuidByte4,
    MSEZeroBit,
    MSEFlushBits,
    MSETransportGuidByte4,
    MSETransportGuidByte5,
    MSETransportPositionX,
    MSETransportOrientation,
    MSETransportGuidByte1,
    MSETransportGuidByte0,
    MSETransportGuidByte6,
    MSETransportTime,
    MSETransportGuidByte7,
    MSETransportSeat,
    MSETransportTime2,
    MSETransportPositionY,
    MSETransportGuidByte3,
    MSETransportGuidByte2,
    MSETransportVehicleId,
    MSETransportPositionZ,
    MSETimestamp,
    MSEFallCosAngle,
    MSEFallHorizontalSpeed,
    MSEFallSinAngle,
    MSEFallVerticalSpeed,
    MSEFallTime,
    MSEPitch,
    MSEGuidByte6,
    MSESplineElevation,
    MSEGuidByte5,
    MSEGuidByte7,
    MSEGuidByte4,
    MSEOrientation,
    MSEGuidByte0,
    MSEGuidByte3,
    MSEGuidByte2,
    MSEGuidByte1,
    MSEEnd,
};

MovementStatusElements const MovementUpdateFlightSpeed[] =
{
    MSEPositionY,
    MSEExtraElement,
    MSEPositionX,
    MSEPositionZ,
    MSEHasMovementFlags,
    MSEHasGuidByte4,
    MSEZeroBit,
    MSEHasGuidByte5,
    MSEHasGuidByte1,
    MSEMovementFlags,
    MSEHasFallData,
    MSEHasGuidByte2,
    MSEHasOrientation,
    MSEHasPitch,
    MSEHasSplineElevation,
    MSEHasGuidByte7,
    MSEHasTimestamp,
    MSEHasTransportData,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte2,
    MSEHasVehicleId,
    MSEHasTransportGuidByte7,
    MSEHasTransportTime2,
    MSEHasGuidByte6,
    MSEHasGuidByte3,
    MSEHasMovementFlags2,
    MSEHasSpline,
    MSEMovementFlags2,
    MSEHasFallDirection,
    MSEHasGuidByte0,
    MSEFlushBits,
    MSESplineElevation,
    MSEPitch,
    MSEGuidByte0,
    MSEGuidByte5,
    MSETransportOrientation,
    MSETransportTime,
    MSETransportGuidByte5,
    MSETransportGuidByte4,
    MSETransportGuidByte6,
    MSETransportPositionZ,
    MSETransportGuidByte7,
    MSETransportGuidByte0,
    MSETransportGuidByte2,
    MSETransportGuidByte3,
    MSETransportPositionY,
    MSETransportVehicleId,
    MSETransportTime2,
    MSETransportGuidByte1,
    MSETransportSeat,
    MSETransportPositionX,
    MSEFallCosAngle,
    MSEFallHorizontalSpeed,
    MSEFallSinAngle,
    MSEFallVerticalSpeed,
    MSEFallTime,
    MSEGuidByte1,
    MSEGuidByte6,
    MSETimestamp,
    MSEGuidByte7,
    MSEGuidByte2,
    MSEGuidByte4,
    MSEOrientation,
    MSEGuidByte3,
    MSEEnd
};

MovementStatusElements const MovementSetCollisionHeight[] =
{
    MSEExtraElement,
    MSEHasGuidByte6,
    MSEHasGuidByte1,
    MSEHasGuidByte4,
    MSEHasGuidByte7,
    MSEHasGuidByte5,
    MSEHasGuidByte2,
    MSEHasGuidByte0,
    MSEHasGuidByte3,
    MSEFlushBits,
    MSEGuidByte6,
    MSEGuidByte0,
    MSEGuidByte4,
    MSEGuidByte3,
    MSEGuidByte5,
    MSECounter,
    MSEGuidByte1,
    MSEGuidByte2,
    MSEGuidByte7,
    MSEExtraElement,
    MSEEnd
};

MovementStatusElements const MovementUpdateCollisionHeight[] =
{
    MSEPositionZ,
    MSEExtraElement,
    MSEPositionX,
    MSEPositionY,
    MSEHasGuidByte6,
    MSEHasGuidByte7,
    MSEHasSplineElevation,
    MSEHasTransportData,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte5,
    MSEHasVehicleId,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte2,
    MSEHasTransportTime2,
    MSEHasGuidByte3,
    MSEHasOrientation,
    MSEHasGuidByte4,
    MSEHasGuidByte5,
    MSEHasTimestamp,
    MSEHasFallData,
    MSEHasGuidByte0,
    MSEHasPitch,
    MSEHasHeightChangeFailed,
    MSEHasGuidByte2,
    MSEHasMovementFlags,
    MSEHasFallDirection,
    MSEHasGuidByte1,
    MSEHasMovementFlags2,
    MSEHasSpline,
    MSEMovementFlags2,
    MSEMovementFlags,
    MSEFlushBits,
    MSEGuidByte3,
    MSETransportGuidByte7,
    MSETransportTime,
    MSETransportGuidByte4,
    MSETransportVehicleId,
    MSETransportTime2,
    MSETransportGuidByte5,
    MSETransportOrientation,
    MSETransportPositionX,
    MSETransportGuidByte6,
    MSETransportGuidByte0,
    MSETransportPositionY,
    MSETransportGuidByte2,
    MSETransportPositionZ,
    MSETransportGuidByte3,
    MSETransportGuidByte1,
    MSETransportSeat,
    MSEPitch,
    MSEGuidByte6,
    MSEFallCosAngle,
    MSEFallSinAngle,
    MSEFallHorizontalSpeed,
    MSEFallVerticalSpeed,
    MSEFallTime,
    MSEGuidByte7,
    MSEOrientation,
    MSEGuidByte0,
    MSEGuidByte5,
    MSEGuidByte4,
    MSESplineElevation,
    MSETimestamp,
    MSEGuidByte2,
    MSEGuidByte1,
    MSEEnd,
};

MovementStatusElements const MovementForceRunSpeedChangeAck[] =
{
    MSECounter,
    MSEPositionX,
    MSEExtraElement,
    MSEPositionZ,
    MSEPositionY,
    MSEHasGuidByte2,
    MSEHasGuidByte4,
    MSEHasGuidByte1,
    MSEHasGuidByte7,
    MSEHasOrientation,
    MSEHasFallData,
    MSEHasGuidByte0,
    MSEHasSpline,
    MSEHasTransportData,
    MSEHasTimestamp,
    MSEHasMovementFlags2,
    MSEHasGuidByte6,
    MSEZeroBit,
    MSEHasSplineElevation,
    MSEHasPitch,
    MSEHasGuidByte5,
    MSEHasMovementFlags,
    MSEHasGuidByte3,
    MSEHasVehicleId,
    MSEHasTransportGuidByte5,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte4,
    MSEMovementFlags,
    MSEHasFallDirection,
    MSEMovementFlags2,
    MSEGuidByte6,
    MSEGuidByte4,
    MSEGuidByte1,
    MSEGuidByte3,
    MSEGuidByte5,
    MSEGuidByte2,
    MSEGuidByte7,
    MSEGuidByte0,
    MSETransportPositionZ,
    MSETransportGuidByte6,
    MSETransportGuidByte1,
    MSETransportPositionY,
    MSETransportGuidByte0,
    MSETransportGuidByte5,
    MSETransportTime2,
    MSETransportPositionX,
    MSETransportTime,
    MSETransportGuidByte7,
    MSETransportOrientation,
    MSETransportGuidByte3,
    MSETransportVehicleId,
    MSETransportGuidByte2,
    MSETransportSeat,
    MSETransportGuidByte4,
    MSEFallVerticalSpeed,
    MSEFallHorizontalSpeed,
    MSEFallSinAngle,
    MSEFallCosAngle,
    MSEFallTime,
    MSESplineElevation,
    MSEPitch,
    MSETimestamp,
    MSEOrientation,
    MSEEnd,
};

MovementStatusElements const MovementSetCollisionHeightAck[] =
{
    MSEExtraElement, // Height
    MSEPositionX,
    MSEPositionZ,
    MSECounter,
    MSEPositionY,
    MSEHasGuidByte6,
    MSEHasGuidByte4,
    MSEExtraElement, // Reason
    MSEHasPitch,
    MSEHasGuidByte5,
    MSEHasHeightChangeFailed,
    MSEHasGuidByte2,
    MSEHasGuidByte1,
    MSEHasFallData,
    MSEHasGuidByte3,
    MSEHasSpline,
    MSEHasGuidByte7,
    MSEHasMovementFlags,
    MSEHasTransportData,
    MSEHasTimestamp,
    MSEHasSplineElevation,
    MSEHasMovementFlags2,
    MSEHasOrientation,
    MSEHasGuidByte0,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte3,
    MSEHasTransportTime2,
    MSEHasVehicleId,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte0,
    MSEMovementFlags2,
    MSEMovementFlags,
    MSEHasFallDirection,
    MSEGuidByte0,
    MSEGuidByte3,
    MSEGuidByte1,
    MSEGuidByte5,
    MSEGuidByte7,
    MSEGuidByte6,
    MSEGuidByte2,
    MSEGuidByte4,
    MSETransportPositionX,
    MSETransportGuidByte4,
    MSETransportTime2,
    MSETransportGuidByte0,
    MSETransportOrientation,
    MSETransportPositionY,
    MSETransportGuidByte7,
    MSETransportSeat,
    MSETransportGuidByte5,
    MSETransportGuidByte2,
    MSETransportTime,
    MSETransportGuidByte6,
    MSETransportGuidByte3,
    MSETransportGuidByte1,
    MSETransportVehicleId,
    MSETransportPositionZ,
    MSEFallVerticalSpeed,
    MSEFallTime,
    MSEFallCosAngle,
    MSEFallSinAngle,
    MSEFallHorizontalSpeed,
    MSETimestamp,
    MSESplineElevation,
    MSEOrientation,
    MSEPitch,
    MSEEnd,
};

MovementStatusElements const MovementForceFlightSpeedChangeAck[] =
{
    MSECounter,
    MSEPositionZ,
    MSEPositionX,
    MSEPositionY,
    MSEExtraElement,
    MSEHasGuidByte4,
    MSEHasGuidByte5,
    MSEZeroBit,
    MSEHasMovementFlags,
    MSEHasSplineElevation,
    MSEHasGuidByte3,
    MSEHasMovementFlags2,
    MSEHasGuidByte7,
    MSEHasTransportData,
    MSEHasGuidByte0,
    MSEHasFallData,
    MSEHasTimestamp,
    MSEHasPitch,
    MSEHasSpline,
    MSEHasOrientation,
    MSEHasGuidByte6,
    MSEHasGuidByte2,
    MSEHasGuidByte1,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte7,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte0,
    MSEHasVehicleId,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte4,
    MSEHasFallDirection,
    MSEMovementFlags2,
    MSEMovementFlags,
    MSEGuidByte5,
    MSEGuidByte6,
    MSEGuidByte1,
    MSEGuidByte7,
    MSEGuidByte3,
    MSEGuidByte0,
    MSEGuidByte2,
    MSEGuidByte4,
    MSETransportGuidByte6,
    MSETransportGuidByte0,
    MSETransportSeat,
    MSETransportTime2,
    MSETransportOrientation,
    MSETransportGuidByte1,
    MSETransportGuidByte5,
    MSETransportVehicleId,
    MSETransportGuidByte2,
    MSETransportPositionZ,
    MSETransportGuidByte7,
    MSETransportGuidByte3,
    MSETransportGuidByte4,
    MSETransportPositionX,
    MSETransportTime,
    MSETransportPositionY,
    MSETimestamp,
    MSESplineElevation,
    MSEFallSinAngle,
    MSEFallCosAngle,
    MSEFallHorizontalSpeed,
    MSEFallTime,
    MSEFallVerticalSpeed,
    MSEPitch,
    MSEOrientation,
    MSEEnd,
};

MovementStatusElements const MovementSetCanFlyAck[] =
{
    MSEPositionY,
    MSECounter,
    MSEPositionX,
    MSEPositionZ,
    MSEHasGuidByte3,
    MSEHasTimestamp,
    MSEHasGuidByte4,
    MSEHasGuidByte0,
    MSEHasOrientation,
    MSEHasFallData,
    MSEHasGuidByte2,
    MSEHasGuidByte5,
    MSEHasSplineElevation,
    MSEHasMovementFlags2,
    MSEZeroBit,
    MSEHasGuidByte7,
    MSEHasSpline,
    MSEHasGuidByte6,
    MSEHasGuidByte1,
    MSEHasMovementFlags,
    MSEHasTransportData,
    MSEHasPitch,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte2,
    MSEHasVehicleId,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte6,
    MSEMovementFlags2,
    MSEMovementFlags,
    MSEHasFallDirection,
    MSEGuidByte1,
    MSEGuidByte0,
    MSEGuidByte2,
    MSEGuidByte3,
    MSEGuidByte7,
    MSEGuidByte6,
    MSEGuidByte4,
    MSEGuidByte5,
    MSETransportTime2,
    MSETransportGuidByte6,
    MSETransportTime,
    MSETransportVehicleId,
    MSETransportGuidByte7,
    MSETransportPositionZ,
    MSETransportGuidByte3,
    MSETransportPositionY,
    MSETransportGuidByte5,
    MSETransportPositionX,
    MSETransportGuidByte2,
    MSETransportOrientation,
    MSETransportSeat,
    MSETransportGuidByte1,
    MSETransportGuidByte0,
    MSETransportGuidByte4,
    MSEFallTime,
    MSEFallSinAngle,
    MSEFallHorizontalSpeed,
    MSEFallCosAngle,
    MSEFallVerticalSpeed,
    MSEPitch,
    MSEOrientation,
    MSETimestamp,
    MSESplineElevation,
    MSEEnd,
};

MovementStatusElements MoveForceSwimBackSpeedChangeAck[] =
{
    MSEExtraElement,
    MSEPositionX,
    MSEPositionZ,
    MSEPositionY,
    MSECounter,
    MSEHasGuidByte7,
    MSEHasTransportData,
    MSEHasGuidByte6,
    MSEHasPitch,
    MSEHasOrientation,
    MSEHasGuidByte2,
    MSEHasMovementFlags,
    MSEHasGuidByte0,
    MSEHasGuidByte5,
    MSEHasGuidByte3,
    MSEHasSpline,
    MSEHasTimestamp,
    MSEZeroBit,
    MSEHasMovementFlags2,
    MSEHasGuidByte4,
    MSEHasGuidByte1,
    MSEHasSplineElevation,
    MSEHasFallData,

    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte7,
    MSEHasVehicleId,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte0,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte2,

    MSEMovementFlags,

    MSEMovementFlags2,

    MSEHasFallDirection,

    MSEGuidByte0,
    MSEGuidByte7,
    MSEGuidByte4,
    MSEGuidByte6,
    MSEGuidByte1,
    MSEGuidByte2,
    MSEGuidByte5,
    MSEGuidByte3,

    MSEFallSinAngle,
    MSEFallCosAngle,
    MSEFallHorizontalSpeed,
    MSEFallVerticalSpeed,
    MSEFallTime,

    MSETransportGuidByte4,
    MSETransportGuidByte6,
    MSETransportGuidByte1,
    MSETransportPositionY,
    MSETransportOrientation,
    MSETransportPositionZ,
    MSETransportGuidByte7,
    MSETransportVehicleId,
    MSETransportTime,
    MSETransportGuidByte3,
    MSETransportGuidByte2,
    MSETransportSeat,
    MSETransportGuidByte0,
    MSETransportTime2,
    MSETransportPositionX,
    MSETransportGuidByte5,

    MSETimestamp,
    MSESplineElevation,
    MSEPitch,
    MSEOrientation,
    MSEEnd,
};

//4.3.4
MovementStatusElements MoveForceFlightBackSpeedChangeAck[] =
{
    MSEPositionY,
    MSEPositionZ,
    MSECounter,
    MSEPositionX,
    MSEExtraElement,
    MSEHasSplineElevation,
    MSEHasPitch,
    MSEHasFallData,
    MSEHasSpline,
    MSEHasGuidByte7,
    MSEHasGuidByte4,
    MSEZeroBit,
    MSEHasGuidByte1,
    MSEHasOrientation,
    MSEHasMovementFlags,
    MSEHasGuidByte5,
    MSEHasGuidByte3,
    MSEHasTransportData,
    MSEHasGuidByte6,
    MSEHasMovementFlags2,
    MSEHasGuidByte2,
    MSEHasGuidByte0,
    MSEHasTimestamp,

    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte1,
    MSEHasVehicleId,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte3,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte4,

    MSEMovementFlags2,

    MSEMovementFlags,

    MSEHasFallDirection,

    MSEGuidByte7,
    MSEGuidByte0,
    MSEGuidByte5,
    MSEGuidByte6,
    MSEGuidByte3,
    MSEGuidByte2,
    MSEGuidByte4,
    MSEGuidByte1,

    MSETransportGuidByte2,
    MSETransportGuidByte0,
    MSETransportTime,
    MSETransportGuidByte3,
    MSETransportOrientation,
    MSETransportGuidByte1,
    MSETransportPositionX,
    MSETransportPositionZ,
    MSETransportGuidByte4,
    MSETransportGuidByte7,
    MSETransportVehicleId,
    MSETransportGuidByte5,
    MSETransportTime2,
    MSETransportPositionY,
    MSETransportSeat,
    MSETransportGuidByte6,

    MSEFallCosAngle,
    MSEFallSinAngle,
    MSEFallHorizontalSpeed,
    MSEFallVerticalSpeed,
    MSEFallTime,

    MSETimestamp,
    MSEPitch,
    MSEOrientation,
    MSESplineElevation,
    MSEEnd,
};

MovementStatusElements const MovementForceSwimSpeedChangeAck[] =
{
    MSEPositionX,
    MSECounter,
    MSEExtraElement,
    MSEPositionY,
    MSEPositionZ,
    MSEHasGuidByte4,
    MSEHasOrientation,
    MSEHasPitch,
    MSEHasTransportData,
    MSEHasMovementFlags,
    MSEHasMovementFlags2,
    MSEHasGuidByte1,
    MSEHasGuidByte3,
    MSEHasFallData,
    MSEHasGuidByte2,
    MSEHasGuidByte7,
    MSEHasTimestamp,
    MSEZeroBit,
    MSEHasGuidByte5,
    MSEHasGuidByte6,
    MSEHasSplineElevation,
    MSEHasSpline,
    MSEHasGuidByte0,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte3,
    MSEHasTransportTime2,
    MSEHasVehicleId,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte2,
    MSEMovementFlags2,
    MSEHasFallDirection,
    MSEMovementFlags,
    MSEGuidByte2,
    MSEGuidByte0,
    MSEGuidByte6,
    MSEGuidByte5,
    MSEGuidByte1,
    MSEGuidByte3,
    MSEGuidByte4,
    MSEGuidByte7,
    MSETransportGuidByte0,
    MSETransportVehicleId,
    MSETransportTime2,
    MSETransportPositionX,
    MSETransportGuidByte7,
    MSETransportSeat,
    MSETransportPositionY,
    MSETransportGuidByte5,
    MSETransportPositionZ,
    MSETransportOrientation,
    MSETransportTime,
    MSETransportGuidByte2,
    MSETransportGuidByte6,
    MSETransportGuidByte3,
    MSETransportGuidByte1,
    MSETransportGuidByte4,
    MSEFallTime,
    MSEFallSinAngle,
    MSEFallCosAngle,
    MSEFallHorizontalSpeed,
    MSEFallVerticalSpeed,
    MSEOrientation,
    MSEPitch,
    MSESplineElevation,
    MSETimestamp,
    MSEEnd,
};


MovementStatusElements const MovementForceWalkSpeedChangeAck[] =
{
    MSEPositionZ,
    MSEPositionY,
    MSEExtraElement,
    MSEPositionX,
    MSECounter,
    MSEHasGuidByte0,
    MSEHasMovementFlags2,
    MSEHasTimestamp,
    MSEHasGuidByte4,
    MSEHasGuidByte5,
    MSEHasGuidByte2,
    MSEHasMovementFlags,
    MSEHasFallData,
    MSEHasOrientation,
    MSEHasSpline,
    MSEZeroBit,
    MSEHasGuidByte3,
    MSEHasGuidByte1,
    MSEHasSplineElevation,
    MSEHasTransportData,
    MSEHasGuidByte7,
    MSEHasGuidByte6,
    MSEHasPitch,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte6,
    MSEHasVehicleId,
    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte3,
    MSEMovementFlags,
    MSEMovementFlags2,
    MSEHasFallDirection,
    MSEGuidByte5,
    MSEGuidByte6,
    MSEGuidByte7,
    MSEGuidByte2,
    MSEGuidByte1,
    MSEGuidByte3,
    MSEGuidByte4,
    MSEGuidByte0,
    MSEFallVerticalSpeed,
    MSEFallCosAngle,
    MSEFallHorizontalSpeed,
    MSEFallSinAngle,
    MSEFallTime,
    MSETransportPositionZ,
    MSETransportGuidByte7,
    MSETransportGuidByte5,
    MSETransportPositionX,
    MSETransportGuidByte0,
    MSETransportTime,
    MSETransportVehicleId,
    MSETransportPositionY,
    MSETransportGuidByte2,
    MSETransportGuidByte4,
    MSETransportGuidByte1,
    MSETransportGuidByte3,
    MSETransportOrientation,
    MSETransportSeat,
    MSETransportGuidByte6,
    MSETransportTime2,
    MSESplineElevation,
    MSETimestamp,
    MSEOrientation,
    MSEPitch,
    MSEEnd,
};

MovementStatusElements const MovementForceRunBackSpeedChangeAck[] =
{
    MSEExtraElement,
    MSECounter,
    MSEPositionX,
    MSEPositionZ,
    MSEPositionY,
    MSEHasGuidByte2,
    MSEHasGuidByte4,
    MSEHasTimestamp,
    MSEHasTransportData,
    MSEHasGuidByte1,
    MSEHasGuidByte0,
    MSEHasGuidByte5,
    MSEHasGuidByte3,
    MSEHasOrientation,
    MSEHasFallData,
    MSEHasMovementFlags2,
    MSEHasMovementFlags,
    MSEHasGuidByte7,
    MSEHasSpline,
    MSEHasPitch,
    MSEHasGuidByte6,
    MSEHasSplineElevation,
    MSEZeroBit,
    MSEHasTransportGuidByte3,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte1,
    MSEHasVehicleId,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte5,
    MSEMovementFlags,
    MSEMovementFlags2,
    MSEHasFallDirection,
    MSEGuidByte0,
    MSEGuidByte7,
    MSEGuidByte2,
    MSEGuidByte4,
    MSEGuidByte3,
    MSEGuidByte6,
    MSEGuidByte5,
    MSEGuidByte1,
    MSEFallTime,
    MSEFallHorizontalSpeed,
    MSEFallSinAngle,
    MSEFallCosAngle,
    MSEFallVerticalSpeed,
    MSETransportGuidByte5,
    MSETransportSeat,
    MSETransportGuidByte6,
    MSETransportGuidByte1,
    MSETransportGuidByte0,
    MSETransportGuidByte2,
    MSETransportPositionY,
    MSETransportVehicleId,
    MSETransportPositionX,
    MSETransportOrientation,
    MSETransportGuidByte3,
    MSETransportTime,
    MSETransportTime2,
    MSETransportGuidByte4,
    MSETransportPositionZ,
    MSETransportGuidByte7,
    MSETimestamp,
    MSESplineElevation,
    MSEOrientation,
    MSEPitch,
    MSEEnd,
};

MovementStatusElements const MovementUpdateRunBackSpeed[] =
{
    MSEHasGuidByte1,
    MSEHasGuidByte2,
    MSEHasGuidByte4,
    MSEHasGuidByte3,
    MSEHasGuidByte6,
    MSEHasGuidByte0,
    MSEZeroBit,
    MSEHasMovementFlags,
    MSEHasGuidByte5,
    MSEHasOrientation,
    MSEMovementFlags,
    MSEHasFallDirection,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte0,
    MSEHasGuidByte7,
    MSEFlushBits,
    MSETransportPositionX,
    MSETransportGuidByte2,
    MSETransportGuidByte5,
    MSETransportGuidByte4,
    MSETransportGuidByte6,
    MSETransportGuidByte0,
    MSETransportGuidByte3,
    MSETransportPositionY,
    MSETransportGuidByte7,
    MSETransportPositionZ,
    MSETransportTime,
    MSETransportSeat,
    MSETransportGuidByte1,
    MSETransportOrientation,
    MSEGuidByte4,
    MSEFallTime,
    MSEFallHorizontalSpeed,
    MSEFallSinAngle,
    MSEFallCosAngle,
    MSEFallVerticalSpeed,
    MSETimestamp,
    MSEGuidByte1,
    MSEOrientation,
    MSEGuidByte0,
    MSEGuidByte5,
    MSEGuidByte3,
    MSEPositionX,
    MSEPositionY,
    MSEPitch,
    MSEGuidByte7,
    MSEExtraElement,
    MSEGuidByte2,
    MSEGuidByte6,
    MSEPositionZ,
    MSEEnd,
};

MovementStatusElements const MovementUpdateWalkSpeed[] =
{
    MSEHasOrientation,
    MSEZeroBit,
    MSEHasGuidByte3,
    MSEHasGuidByte2,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte5,
    MSEHasGuidByte7,
    MSEHasGuidByte5,
    MSEHasGuidByte1,
    MSEHasGuidByte0,
    MSEHasMovementFlags,
    MSEHasGuidByte6,
    MSEHasFallDirection,
    MSEMovementFlags,
    MSEHasGuidByte4,
    MSEFlushBits,
    MSEPitch,
    MSETransportGuidByte6,
    MSETransportGuidByte0,
    MSETransportGuidByte4,
    MSETransportGuidByte2,
    MSETransportPositionX,
    MSETransportGuidByte7,
    MSETransportTime,
    MSETransportPositionZ,
    MSETransportSeat,
    MSETransportGuidByte5,
    MSETransportOrientation,
    MSETransportGuidByte1,
    MSETransportPositionY,
    MSETransportGuidByte3,
    MSEFallVerticalSpeed,
    MSEFallHorizontalSpeed,
    MSEFallSinAngle,
    MSEFallCosAngle,
    MSEFallTime,
    MSEGuidByte1,
    MSEGuidByte4,
    MSEGuidByte2,
    MSEGuidByte6,
    MSEGuidByte7,
    MSETimestamp,
    MSEOrientation,
    MSEPositionY,
    MSEGuidByte0,
    MSEPositionZ,
    MSEPositionX,
    MSEGuidByte3,
    MSEGuidByte5,
    MSEExtraElement,
    MSEEnd,
};

MovementStatusElements const ForceMoveRootAck[] =
{
    MSEPositionY,
    MSEPositionZ,
    MSECounter,
    MSEPositionX,
    MSEHasGuidByte3,
    MSEHasTimestamp,
    MSEHasTransportData,
    MSEHasPitch,
    MSEHasGuidByte2,
    MSEHasOrientation,
    MSEHasSplineElevation,
    MSEHasFallData,
    MSEHasSpline,
    MSEHasGuidByte4,
    MSEHasGuidByte0,
    MSEHasGuidByte6,
    MSEHasGuidByte1,
    MSEHasGuidByte7,
    MSEHasMovementFlags2,
    MSEHasMovementFlags,
    MSEZeroBit,
    MSEHasGuidByte5,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte2,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte4,
    MSEHasVehicleId,
    MSEHasTransportGuidByte5,
    MSEMovementFlags2,
    MSEMovementFlags,
    MSEHasFallDirection,
    MSEGuidByte5,
    MSEGuidByte3,
    MSEGuidByte1,
    MSEGuidByte7,
    MSEGuidByte4,
    MSEGuidByte0,
    MSEGuidByte6,
    MSEGuidByte2,
    MSETransportGuidByte5,
    MSETransportGuidByte4,
    MSETransportOrientation,
    MSETransportPositionZ,
    MSETransportVehicleId,
    MSETransportTime2,
    MSETransportGuidByte7,
    MSETransportGuidByte2,
    MSETransportGuidByte0,
    MSETransportTime,
    MSETransportGuidByte6,
    MSETransportGuidByte3,
    MSETransportPositionX,
    MSETransportGuidByte1,
    MSETransportPositionY,
    MSETransportSeat,
    MSETimestamp,
    MSEFallVerticalSpeed,
    MSEFallHorizontalSpeed,
    MSEFallCosAngle,
    MSEFallSinAngle,
    MSEFallTime,
    MSEOrientation,
    MSESplineElevation,
    MSEPitch,
    MSEEnd,
};

MovementStatusElements const ForceMoveUnrootAck[] =
{
    MSECounter,
    MSEPositionZ,
    MSEPositionY,
    MSEPositionX,
    MSEHasGuidByte7,
    MSEHasSplineElevation,
    MSEHasSpline,
    MSEHasGuidByte5,
    MSEHasGuidByte4,
    MSEZeroBit,
    MSEHasTimestamp,
    MSEHasMovementFlags,
    MSEHasOrientation,
    MSEHasPitch,
    MSEHasGuidByte3,
    MSEHasGuidByte1,
    MSEHasTransportData,
    MSEHasMovementFlags2,
    MSEHasGuidByte2,
    MSEHasGuidByte0,
    MSEHasFallData,
    MSEHasGuidByte6,
    MSEHasFallDirection,
    MSEHasTransportGuidByte0,
    MSEHasVehicleId,
    MSEHasTransportGuidByte6,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte1,
    MSEMovementFlags2,
    MSEMovementFlags,
    MSEGuidByte7,
    MSEGuidByte1,
    MSEGuidByte0,
    MSEGuidByte6,
    MSEGuidByte2,
    MSEGuidByte4,
    MSEGuidByte5,
    MSEGuidByte3,
    MSETransportGuidByte6,
    MSETransportPositionZ,
    MSETransportGuidByte2,
    MSETransportGuidByte3,
    MSETransportPositionY,
    MSETransportVehicleId,
    MSETransportGuidByte5,
    MSETransportSeat,
    MSETransportGuidByte0,
    MSETransportTime,
    MSETransportTime2,
    MSETransportGuidByte4,
    MSETransportOrientation,
    MSETransportPositionX,
    MSETransportGuidByte1,
    MSETransportGuidByte7,
    MSEFallSinAngle,
    MSEFallHorizontalSpeed,
    MSEFallCosAngle,
    MSEFallVerticalSpeed,
    MSEFallTime,
    MSETimestamp,
    MSESplineElevation,
    MSEOrientation,
    MSEPitch,
    MSEEnd,
};

//4.3.4
MovementStatusElements MoveUpdateSwimBackSpeed[] =
{
    MSEHasGuidByte7,
    MSEHasGuidByte2,
    MSEHasTransportData,
    MSEHasGuidByte1,
    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte6,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte5,
    MSEHasVehicleId,
    MSEHasPitch,
    MSEHasOrientation,
    MSEZeroBit,
    MSEHasGuidByte5,
    MSEHasGuidByte3,
    MSEHasGuidByte6,
    MSEHasGuidByte4,
    MSEHasSpline,
    MSEHasMovementFlags,
    MSEHasGuidByte0,
    MSEHasFallData,
    MSEHasFallDirection,
    MSEMovementFlags,
    MSEHasTimestamp,
    MSEHasSplineElevation,
    MSEHasMovementFlags2,
    MSEMovementFlags2,
    MSEFlushBits,
    MSEGuidByte0,
    MSEGuidByte4,
    MSEPositionY,
    MSETransportGuidByte7,
    MSETransportVehicleId,
    MSETransportGuidByte6,
    MSETransportGuidByte4,
    MSETransportGuidByte2,
    MSETransportGuidByte3,
    MSETransportOrientation,
    MSETransportGuidByte5,
    MSETransportTime,
    MSETransportGuidByte0,
    MSETransportGuidByte1,
    MSETransportPositionX,
    MSETransportPositionZ,
    MSETransportTime2,
    MSETransportPositionY,
    MSETransportSeat,
    MSEFallSinAngle,
    MSEFallCosAngle,
    MSEFallHorizontalSpeed,
    MSEFallVerticalSpeed,
    MSEFallTime,
    MSEPitch,
    MSEGuidByte2,
    MSEGuidByte7,
    MSEExtraElement,
    MSESplineElevation,
    MSEPositionZ,
    MSEGuidByte3,
    MSEPositionX,
    MSETimestamp,
    MSEGuidByte5,
    MSEOrientation,
    MSEGuidByte6,
    MSEGuidByte1,
    MSEEnd
};

MovementStatusElements const MovementFallReset[] =
{
    MSEPositionZ,
    MSEPositionX,
    MSEPositionY,
    MSEHasGuidByte1,
    MSEHasTimestamp,
    MSEHasMovementFlags,
    MSEZeroBit,
    MSEHasGuidByte6,
    MSEHasSplineElevation,
    MSEHasPitch,
    MSEHasGuidByte3,
    MSEHasTransportData,
    MSEHasGuidByte2,
    MSEHasMovementFlags2,
    MSEHasOrientation,
    MSEHasGuidByte4,
    MSEHasGuidByte5,
    MSEHasSpline,
    MSEHasGuidByte7,
    MSEHasGuidByte0,
    MSEHasFallData,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte4,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte2,
    MSEHasVehicleId,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte3,
    MSEHasFallDirection,
    MSEMovementFlags2,
    MSEMovementFlags,
    MSEGuidByte4,
    MSEGuidByte0,
    MSEGuidByte1,
    MSEGuidByte7,
    MSEGuidByte5,
    MSEGuidByte2,
    MSEGuidByte3,
    MSEGuidByte6,
    MSETransportPositionX,
    MSETransportGuidByte7,
    MSETransportGuidByte2,
    MSETransportGuidByte3,
    MSETransportGuidByte5,
    MSETransportPositionY,
    MSETransportPositionZ,
    MSETransportSeat,
    MSETransportTime2,
    MSETransportGuidByte6,
    MSETransportVehicleId,
    MSETransportTime,
    MSETransportGuidByte0,
    MSETransportOrientation,
    MSETransportGuidByte4,
    MSETransportGuidByte1,
    MSEFallVerticalSpeed,
    MSEFallSinAngle,
    MSEFallCosAngle,
    MSEFallHorizontalSpeed,
    MSEFallTime,
    MSEOrientation,
    MSETimestamp,
    MSESplineElevation,
    MSEPitch,
    MSEEnd,
};

MovementStatusElements const MovementFeatherFallAck[] =
{
    MSEPositionZ,
    MSECounter,
    MSEPositionY,
    MSEPositionX,
    MSEZeroBit,
    MSEHasGuidByte3,
    MSEHasSplineElevation,
    MSEHasGuidByte1,
    MSEHasPitch,
    MSEHasGuidByte2,
    MSEHasSpline,
    MSEHasTimestamp,
    MSEHasGuidByte5,
    MSEHasFallData,
    MSEHasOrientation,
    MSEHasTransportData,
    MSEHasGuidByte7,
    MSEHasMovementFlags2,
    MSEHasGuidByte6,
    MSEHasMovementFlags,
    MSEHasGuidByte0,
    MSEHasGuidByte4,
    MSEHasTransportGuidByte6,
    MSEHasVehicleId,
    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte5,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte0,
    MSEHasFallDirection,
    MSEMovementFlags2,
    MSEMovementFlags,
    MSEGuidByte6,
    MSEGuidByte1,
    MSEGuidByte7,
    MSEGuidByte0,
    MSEGuidByte5,
    MSEGuidByte4,
    MSEGuidByte3,
    MSEGuidByte2,
    MSETransportVehicleId,
    MSETransportOrientation,
    MSETransportPositionZ,
    MSETransportGuidByte7,
    MSETransportGuidByte5,
    MSETransportGuidByte2,
    MSETransportPositionX,
    MSETransportGuidByte1,
    MSETransportGuidByte6,
    MSETransportTime2,
    MSETransportTime,
    MSETransportPositionY,
    MSETransportGuidByte4,
    MSETransportGuidByte0,
    MSETransportSeat,
    MSETransportGuidByte3,
    MSETimestamp,
    MSESplineElevation,
    MSEOrientation,
    MSEFallVerticalSpeed,
    MSEFallSinAngle,
    MSEFallHorizontalSpeed,
    MSEFallCosAngle,
    MSEFallTime,
    MSEPitch,
    MSEEnd,
};

MovementStatusElements const MovementGravityDisableAck[] =
{
    MSEPositionZ,
    MSEPositionY,
    MSECounter,
    MSEPositionX,
    MSEHasGuidByte3,
    MSEHasTransportData,
    MSEHasGuidByte4,
    MSEHasGuidByte5,
    MSEHasMovementFlags,
    MSEHasOrientation,
    MSEHasSpline,
    MSEHasGuidByte6,
    MSEHasGuidByte0,
    MSEHasGuidByte7,
    MSEHasSplineElevation,
    MSEHasTimestamp,
    MSEHasPitch,
    MSEHasMovementFlags2,
    MSEZeroBit,
    MSEHasGuidByte2,
    MSEHasFallData,
    MSEHasGuidByte1,
    MSEHasTransportGuidByte2,
    MSEHasVehicleId,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte4,
    MSEHasTransportTime2,
    MSEMovementFlags,
    MSEMovementFlags2,
    MSEHasFallDirection,
    MSEGuidByte0,
    MSEGuidByte2,
    MSEGuidByte1,
    MSEGuidByte3,
    MSEGuidByte5,
    MSEGuidByte7,
    MSEGuidByte4,
    MSEGuidByte6,
    MSETransportPositionZ,
    MSETransportGuidByte2,
    MSETransportGuidByte5,
    MSETransportGuidByte3,
    MSETransportGuidByte4,
    MSETransportPositionY,
    MSETransportTime,
    MSETransportSeat,
    MSETransportGuidByte6,
    MSETransportGuidByte1,
    MSETransportGuidByte0,
    MSETransportOrientation,
    MSETransportTime2,
    MSETransportPositionX,
    MSETransportGuidByte7,
    MSETransportVehicleId,
    MSEFallSinAngle,
    MSEFallCosAngle,
    MSEFallHorizontalSpeed,
    MSEFallTime,
    MSEFallVerticalSpeed,
    MSEOrientation,
    MSESplineElevation,
    MSETimestamp,
    MSEPitch,
    MSEEnd,
};

MovementStatusElements const MovementGravityEnableAck[] =
{
    MSEPositionZ,
    MSEPositionX,
    MSECounter,
    MSEPositionY,
    MSEHasSplineElevation,
    MSEHasMovementFlags2,
    MSEHasGuidByte6,
    MSEHasOrientation,
    MSEZeroBit,
    MSEHasGuidByte5,
    MSEHasSpline,
    MSEHasGuidByte3,
    MSEHasTransportData,
    MSEHasPitch,
    MSEHasGuidByte1,
    MSEHasTimestamp,
    MSEHasGuidByte2,
    MSEHasGuidByte4,
    MSEHasGuidByte7,
    MSEHasMovementFlags,
    MSEHasFallData,
    MSEHasGuidByte0,
    MSEHasVehicleId,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte5,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte6,
    MSEHasFallDirection,
    MSEMovementFlags,
    MSEMovementFlags2,
    MSEGuidByte5,
    MSEGuidByte4,
    MSEGuidByte1,
    MSEGuidByte7,
    MSEGuidByte0,
    MSEGuidByte2,
    MSEGuidByte3,
    MSEGuidByte6,
    MSEFallTime,
    MSEFallHorizontalSpeed,
    MSEFallCosAngle,
    MSEFallSinAngle,
    MSEFallVerticalSpeed,
    MSETransportGuidByte1,
    MSETransportPositionX,
    MSETransportVehicleId,
    MSETransportOrientation,
    MSETransportGuidByte2,
    MSETransportGuidByte0,
    MSETransportGuidByte7,
    MSETransportGuidByte6,
    MSETransportSeat,
    MSETransportGuidByte3,
    MSETransportGuidByte4,
    MSETransportPositionZ,
    MSETransportTime2,
    MSETransportGuidByte5,
    MSETransportTime,
    MSETransportPositionY,
    MSESplineElevation,
    MSEOrientation,
    MSEPitch,
    MSETimestamp,
    MSEEnd,
};

MovementStatusElements const MovementHoverAck[] =
{
    MSECounter,
    MSEPositionZ,
    MSEPositionY,
    MSEPositionX,
    MSEHasGuidByte4,
    MSEHasTransportData,
    MSEHasGuidByte2,
    MSEHasTimestamp,
    MSEHasSpline,
    MSEHasMovementFlags,
    MSEHasGuidByte1,
    MSEHasPitch,
    MSEHasGuidByte0,
    MSEHasGuidByte6,
    MSEHasGuidByte7,
    MSEHasGuidByte5,
    MSEZeroBit,
    MSEHasFallData,
    MSEHasMovementFlags2,
    MSEHasSplineElevation,
    MSEHasOrientation,
    MSEHasGuidByte3,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte6,
    MSEHasVehicleId,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte7,
    MSEHasTransportTime2,
    MSEMovementFlags,
    MSEMovementFlags2,
    MSEHasFallDirection,
    MSEGuidByte1,
    MSEGuidByte4,
    MSEGuidByte7,
    MSEGuidByte2,
    MSEGuidByte5,
    MSEGuidByte6,
    MSEGuidByte3,
    MSEGuidByte0,
    MSETimestamp,
    MSEFallSinAngle,
    MSEFallCosAngle,
    MSEFallHorizontalSpeed,
    MSEFallTime,
    MSEFallVerticalSpeed,
    MSEOrientation,
    MSETransportGuidByte1,
    MSETransportVehicleId,
    MSETransportGuidByte2,
    MSETransportGuidByte7,
    MSETransportGuidByte3,
    MSETransportGuidByte4,
    MSETransportSeat,
    MSETransportPositionX,
    MSETransportPositionZ,
    MSETransportOrientation,
    MSETransportTime,
    MSETransportGuidByte0,
    MSETransportPositionY,
    MSETransportGuidByte5,
    MSETransportTime2,
    MSETransportGuidByte6,
    MSESplineElevation,
    MSEPitch,
    MSEEnd,
};

MovementStatusElements const MovementKnockBackAck[] =
{
    MSEPositionY,
    MSEPositionZ,
    MSECounter,
    MSEPositionX,
    MSEHasGuidByte6,
    MSEHasOrientation,
    MSEHasPitch,
    MSEHasSplineElevation,
    MSEHasGuidByte3,
    MSEHasGuidByte4,
    MSEHasGuidByte1,
    MSEHasGuidByte2,
    MSEHasSpline,
    MSEHasGuidByte7,
    MSEZeroBit,
    MSEHasMovementFlags2,
    MSEHasTimestamp,
    MSEHasGuidByte0,
    MSEHasMovementFlags,
    MSEHasTransportData,
    MSEHasGuidByte5,
    MSEHasFallData,
    MSEMovementFlags,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte1,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte0,
    MSEHasVehicleId,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte7,
    MSEMovementFlags2,
    MSEHasFallDirection,
    MSEGuidByte4,
    MSEGuidByte5,
    MSEGuidByte1,
    MSEGuidByte6,
    MSEGuidByte0,
    MSEGuidByte3,
    MSEGuidByte2,
    MSEGuidByte7,
    MSEFallSinAngle,
    MSEFallHorizontalSpeed,
    MSEFallCosAngle,
    MSEFallTime,
    MSEFallVerticalSpeed,
    MSETimestamp,
    MSETransportPositionY,
    MSETransportGuidByte4,
    MSETransportTime2,
    MSETransportGuidByte7,
    MSETransportOrientation,
    MSETransportGuidByte6,
    MSETransportTime,
    MSETransportGuidByte3,
    MSETransportGuidByte1,
    MSETransportVehicleId,
    MSETransportGuidByte2,
    MSETransportPositionZ,
    MSETransportGuidByte0,
    MSETransportGuidByte5,
    MSETransportPositionX,
    MSETransportSeat,
    MSEPitch,
    MSESplineElevation,
    MSEOrientation,
    MSEEnd,
};

MovementStatusElements const MovementWaterWalkAck[] =
{
    MSEPositionY,
    MSEPositionZ,
    MSECounter,
    MSEPositionX,
    MSEHasTimestamp,
    MSEHasPitch,
    MSEHasGuidByte5,
    MSEHasGuidByte0,
    MSEHasGuidByte7,
    MSEHasOrientation,
    MSEHasGuidByte1,
    MSEHasMovementFlags2,
    MSEHasGuidByte2,
    MSEHasMovementFlags,
    MSEHasGuidByte3,
    MSEHasTransportData,
    MSEHasGuidByte6,
    MSEHasFallData,
    MSEHasGuidByte4,
    MSEZeroBit,
    MSEHasSplineElevation,
    MSEHasSpline,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte5,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte3,
    MSEHasVehicleId,
    MSEHasTransportGuidByte4,
    MSEMovementFlags,
    MSEHasFallDirection,
    MSEMovementFlags2,
    MSEGuidByte2,
    MSEGuidByte7,
    MSEGuidByte3,
    MSEGuidByte5,
    MSEGuidByte6,
    MSEGuidByte0,
    MSEGuidByte4,
    MSEGuidByte1,
    MSETransportPositionX,
    MSETransportGuidByte1,
    MSETransportVehicleId,
    MSETransportGuidByte0,
    MSETransportOrientation,
    MSETransportGuidByte7,
    MSETransportPositionY,
    MSETransportTime2,
    MSETransportTime,
    MSETransportGuidByte5,
    MSETransportSeat,
    MSETransportPositionZ,
    MSETransportGuidByte3,
    MSETransportGuidByte2,
    MSETransportGuidByte6,
    MSETransportGuidByte4,
    MSESplineElevation,
    MSEFallCosAngle,
    MSEFallHorizontalSpeed,
    MSEFallSinAngle,
    MSEFallVerticalSpeed,
    MSEFallTime,
    MSEOrientation,
    MSETimestamp,
    MSEPitch,
    MSEEnd
};

MovementStatusElements const MovementUpdateKnockBack[] =
{
    MSEZeroBit,
    MSEHasGuidByte4,
    MSEHasMovementFlags,
    MSEHasGuidByte1,
    MSEHasGuidByte0,
    MSEHasGuidByte3,
    MSEHasGuidByte2,
    MSEHasGuidByte7,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte5,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte3,
    MSEHasGuidByte5,
    MSEHasGuidByte6,
    MSEMovementFlags,
    MSEHasFallDirection,
    MSEHasOrientation,
    MSEFlushBits,
    MSEOrientation,
    MSEFallSinAngle,
    MSEFallHorizontalSpeed,
    MSEFallCosAngle,
    MSEFallTime,
    MSEFallVerticalSpeed,
    MSEGuidByte3,
    MSETransportGuidByte5,
    MSETransportGuidByte7,
    MSETransportSeat,
    MSETransportGuidByte3,
    MSETransportGuidByte6,
    MSETransportPositionZ,
    MSETransportGuidByte1,
    MSETransportPositionY,
    MSETransportPositionX,
    MSETransportGuidByte2,
    MSETransportGuidByte0,
    MSETransportOrientation,
    MSETransportTime,
    MSETransportGuidByte4,
    MSEPitch,
    MSEPositionZ,
    MSETimestamp,
    MSEPositionX,
    MSEGuidByte4,
    MSEGuidByte6,
    MSEGuidByte7,
    MSEGuidByte2,
    MSEGuidByte1,
    MSEPositionY,
    MSEGuidByte0,
    MSEGuidByte5,
    MSEEnd,
};

MovementStatusElements const SplineMoveSetWalkSpeed[] =
{
    MSEHasGuidByte0,
    MSEHasGuidByte6,
    MSEHasGuidByte7,
    MSEHasGuidByte3,
    MSEHasGuidByte5,
    MSEHasGuidByte1,
    MSEHasGuidByte2,
    MSEHasGuidByte4,
    MSEGuidByte0,
    MSEGuidByte4,
    MSEGuidByte7,
    MSEGuidByte1,
    MSEGuidByte5,
    MSEGuidByte3,
    MSEExtraElement,
    MSEGuidByte6,
    MSEGuidByte2,
    MSEEnd,
};

MovementStatusElements const SplineMoveSetRunSpeed[] =
{
    MSEHasGuidByte4,
    MSEHasGuidByte0,
    MSEHasGuidByte5,
    MSEHasGuidByte7,
    MSEHasGuidByte6,
    MSEHasGuidByte3,
    MSEHasGuidByte1,
    MSEHasGuidByte2,
    MSEGuidByte0,
    MSEGuidByte7,
    MSEGuidByte6,
    MSEGuidByte5,
    MSEGuidByte3,
    MSEGuidByte4,
    MSEExtraElement,
    MSEGuidByte2,
    MSEGuidByte1,
    MSEEnd,
};

MovementStatusElements const SplineMoveSetRunBackSpeed[] =
{
    MSEHasGuidByte1,
    MSEHasGuidByte2,
    MSEHasGuidByte6,
    MSEHasGuidByte0,
    MSEHasGuidByte3,
    MSEHasGuidByte7,
    MSEHasGuidByte5,
    MSEHasGuidByte4,
    MSEGuidByte1,
    MSEExtraElement,
    MSEGuidByte2,
    MSEGuidByte4,
    MSEGuidByte0,
    MSEGuidByte3,
    MSEGuidByte6,
    MSEGuidByte5,
    MSEGuidByte7,
    MSEEnd,
};

MovementStatusElements const SplineMoveSetSwimSpeed[] =
{
    MSEHasGuidByte4,
    MSEHasGuidByte2,
    MSEHasGuidByte5,
    MSEHasGuidByte0,
    MSEHasGuidByte7,
    MSEHasGuidByte6,
    MSEHasGuidByte3,
    MSEHasGuidByte1,
    MSEGuidByte5,
    MSEGuidByte6,
    MSEGuidByte1,
    MSEGuidByte0,
    MSEGuidByte2,
    MSEGuidByte4,
    MSEExtraElement,
    MSEGuidByte7,
    MSEGuidByte3,
    MSEEnd,
};

MovementStatusElements const SplineMoveSetSwimBackSpeed[] =
{
    MSEHasGuidByte0,
    MSEHasGuidByte1,
    MSEHasGuidByte3,
    MSEHasGuidByte6,
    MSEHasGuidByte4,
    MSEHasGuidByte5,
    MSEHasGuidByte7,
    MSEHasGuidByte2,
    MSEGuidByte5,
    MSEGuidByte3,
    MSEGuidByte1,
    MSEGuidByte0,
    MSEGuidByte7,
    MSEGuidByte6,
    MSEExtraElement,
    MSEGuidByte4,
    MSEGuidByte2,
    MSEEnd,
};

MovementStatusElements const SplineMoveSetTurnRate[] =
{
    MSEHasGuidByte2,
    MSEHasGuidByte4,
    MSEHasGuidByte6,
    MSEHasGuidByte1,
    MSEHasGuidByte3,
    MSEHasGuidByte5,
    MSEHasGuidByte7,
    MSEHasGuidByte0,
    MSEExtraElement,
    MSEGuidByte1,
    MSEGuidByte5,
    MSEGuidByte3,
    MSEGuidByte2,
    MSEGuidByte7,
    MSEGuidByte4,
    MSEGuidByte6,
    MSEGuidByte0,
    MSEEnd,
};

MovementStatusElements const SplineMoveSetFlightSpeed[] =
{
    MSEHasGuidByte7,
    MSEHasGuidByte4,
    MSEHasGuidByte0,
    MSEHasGuidByte1,
    MSEHasGuidByte3,
    MSEHasGuidByte6,
    MSEHasGuidByte5,
    MSEHasGuidByte2,
    MSEGuidByte0,
    MSEGuidByte5,
    MSEGuidByte4,
    MSEGuidByte7,
    MSEGuidByte3,
    MSEGuidByte2,
    MSEGuidByte1,
    MSEGuidByte6,
    MSEExtraElement,
    MSEEnd,
};

MovementStatusElements const SplineMoveSetFlightBackSpeed[] =
{
    MSEHasGuidByte2,
    MSEHasGuidByte1,
    MSEHasGuidByte6,
    MSEHasGuidByte5,
    MSEHasGuidByte0,
    MSEHasGuidByte3,
    MSEHasGuidByte4,
    MSEHasGuidByte7,
    MSEGuidByte5,
    MSEExtraElement,
    MSEGuidByte6,
    MSEGuidByte1,
    MSEGuidByte0,
    MSEGuidByte2,
    MSEGuidByte3,
    MSEGuidByte7,
    MSEGuidByte4,
    MSEEnd,
};

MovementStatusElements const SplineMoveSetPitchRate[] =
{
    MSEHasGuidByte3,
    MSEHasGuidByte5,
    MSEHasGuidByte6,
    MSEHasGuidByte1,
    MSEHasGuidByte0,
    MSEHasGuidByte4,
    MSEHasGuidByte7,
    MSEHasGuidByte2,
    MSEGuidByte1,
    MSEGuidByte5,
    MSEGuidByte7,
    MSEGuidByte0,
    MSEGuidByte6,
    MSEGuidByte3,
    MSEGuidByte2,
    MSEExtraElement,
    MSEGuidByte4,
    MSEEnd,
};

MovementStatusElements const MoveSetWalkSpeed[] =
{
    MSEHasGuidByte0,
    MSEHasGuidByte4,
    MSEHasGuidByte5,
    MSEHasGuidByte2,
    MSEHasGuidByte3,
    MSEHasGuidByte1,
    MSEHasGuidByte6,
    MSEHasGuidByte7,
    MSEGuidByte6,
    MSEGuidByte1,
    MSEGuidByte5,
    MSEExtraElement,
    MSEGuidByte2,
    MSECounter,
    MSEGuidByte4,
    MSEGuidByte0,
    MSEGuidByte7,
    MSEGuidByte3,
    MSEEnd,
};

MovementStatusElements const MoveSetRunSpeed[] =
{
    MSEHasGuidByte6,
    MSEHasGuidByte1,
    MSEHasGuidByte5,
    MSEHasGuidByte2,
    MSEHasGuidByte7,
    MSEHasGuidByte0,
    MSEHasGuidByte3,
    MSEHasGuidByte4,
    MSEGuidByte5,
    MSEGuidByte3,
    MSEGuidByte1,
    MSEGuidByte4,
    MSECounter,
    MSEExtraElement,
    MSEGuidByte6,
    MSEGuidByte0,
    MSEGuidByte7,
    MSEGuidByte2,
    MSEEnd,
};

MovementStatusElements const MoveSetRunBackSpeed[] =
{
    MSEHasGuidByte0,
    MSEHasGuidByte6,
    MSEHasGuidByte2,
    MSEHasGuidByte1,
    MSEHasGuidByte3,
    MSEHasGuidByte4,
    MSEHasGuidByte5,
    MSEHasGuidByte7,
    MSEGuidByte5,
    MSECounter,
    MSEExtraElement,
    MSEGuidByte0,
    MSEGuidByte4,
    MSEGuidByte7,
    MSEGuidByte3,
    MSEGuidByte1,
    MSEGuidByte2,
    MSEGuidByte6,
    MSEEnd,
};

MovementStatusElements const MoveSetSwimSpeed[] =
{
    MSEHasGuidByte5,
    MSEHasGuidByte4,
    MSEHasGuidByte7,
    MSEHasGuidByte3,
    MSEHasGuidByte2,
    MSEHasGuidByte0,
    MSEHasGuidByte1,
    MSEHasGuidByte6,
    MSEGuidByte0,
    MSECounter,
    MSEGuidByte6,
    MSEGuidByte3,
    MSEGuidByte5,
    MSEGuidByte2,
    MSEExtraElement,
    MSEGuidByte1,
    MSEGuidByte7,
    MSEGuidByte4,
    MSEEnd,
};

MovementStatusElements const MoveSetSwimBackSpeed[] =
{
    MSEHasGuidByte4,
    MSEHasGuidByte2,
    MSEHasGuidByte3,
    MSEHasGuidByte6,
    MSEHasGuidByte5,
    MSEHasGuidByte1,
    MSEHasGuidByte0,
    MSEHasGuidByte7,
    MSECounter,
    MSEGuidByte0,
    MSEGuidByte3,
    MSEGuidByte4,
    MSEGuidByte6,
    MSEGuidByte5,
    MSEGuidByte1,
    MSEExtraElement,
    MSEGuidByte7,
    MSEGuidByte2,
    MSEEnd,
};

MovementStatusElements const MoveSetTurnRate[] =
{
    MSEHasGuidByte7,
    MSEHasGuidByte2,
    MSEHasGuidByte1,
    MSEHasGuidByte0,
    MSEHasGuidByte4,
    MSEHasGuidByte5,
    MSEHasGuidByte6,
    MSEHasGuidByte3,
    MSEGuidByte5,
    MSEGuidByte7,
    MSEGuidByte2,
    MSEExtraElement,
    MSEGuidByte3,
    MSEGuidByte1,
    MSEGuidByte0,
    MSECounter,
    MSEGuidByte6,
    MSEGuidByte4,
    MSEEnd,
};

MovementStatusElements const MoveSetFlightSpeed[] =
{
    MSEHasGuidByte0,
    MSEHasGuidByte5,
    MSEHasGuidByte1,
    MSEHasGuidByte6,
    MSEHasGuidByte3,
    MSEHasGuidByte2,
    MSEHasGuidByte7,
    MSEHasGuidByte4,
    MSEGuidByte0,
    MSEGuidByte1,
    MSEGuidByte7,
    MSEGuidByte5,
    MSEExtraElement,
    MSECounter,
    MSEGuidByte2,
    MSEGuidByte6,
    MSEGuidByte3,
    MSEGuidByte4,
    MSEEnd,
};

MovementStatusElements const MoveSetFlightBackSpeed[] =
{
    MSEHasGuidByte1,
    MSEHasGuidByte2,
    MSEHasGuidByte6,
    MSEHasGuidByte4,
    MSEHasGuidByte7,
    MSEHasGuidByte3,
    MSEHasGuidByte0,
    MSEHasGuidByte5,
    MSEGuidByte3,
    MSECounter,
    MSEGuidByte6,
    MSEExtraElement,
    MSEGuidByte1,
    MSEGuidByte2,
    MSEGuidByte4,
    MSEGuidByte0,
    MSEGuidByte5,
    MSEGuidByte7,
    MSEEnd,
};

MovementStatusElements const MoveSetPitchRate[] =
{
    MSEHasGuidByte1,
    MSEHasGuidByte2,
    MSEHasGuidByte6,
    MSEHasGuidByte7,
    MSEHasGuidByte0,
    MSEHasGuidByte3,
    MSEHasGuidByte5,
    MSEHasGuidByte4,
    MSEExtraElement,
    MSEGuidByte6,
    MSEGuidByte4,
    MSEGuidByte0,
    MSECounter,
    MSEGuidByte1,
    MSEGuidByte2,
    MSEGuidByte7,
    MSEGuidByte3,
    MSEGuidByte5,
    MSEEnd,
};

MovementStatusElements const SplineMoveSetWalkMode[] =
{
    MSEHasGuidByte7,
    MSEHasGuidByte6,
    MSEHasGuidByte5,
    MSEHasGuidByte1,
    MSEHasGuidByte3,
    MSEHasGuidByte4,
    MSEHasGuidByte2,
    MSEHasGuidByte0,
    MSEGuidByte4,
    MSEGuidByte2,
    MSEGuidByte1,
    MSEGuidByte6,
    MSEGuidByte5,
    MSEGuidByte0,
    MSEGuidByte7,
    MSEGuidByte3,
    MSEEnd,
};

MovementStatusElements const SplineMoveSetRunMode[] =
{
    MSEHasGuidByte5,
    MSEHasGuidByte6,
    MSEHasGuidByte3,
    MSEHasGuidByte7,
    MSEHasGuidByte2,
    MSEHasGuidByte0,
    MSEHasGuidByte4,
    MSEHasGuidByte1,
    MSEGuidByte7,
    MSEGuidByte0,
    MSEGuidByte4,
    MSEGuidByte6,
    MSEGuidByte5,
    MSEGuidByte1,
    MSEGuidByte2,
    MSEGuidByte3,
    MSEEnd,
};

MovementStatusElements const SplineMoveGravityDisable[] =
{
    MSEHasGuidByte7,
    MSEHasGuidByte3,
    MSEHasGuidByte4,
    MSEHasGuidByte2,
    MSEHasGuidByte5,
    MSEHasGuidByte1,
    MSEHasGuidByte0,
    MSEHasGuidByte6,
    MSEGuidByte7,
    MSEGuidByte1,
    MSEGuidByte3,
    MSEGuidByte4,
    MSEGuidByte6,
    MSEGuidByte2,
    MSEGuidByte5,
    MSEGuidByte0,
    MSEEnd,
};

MovementStatusElements const SplineMoveGravityEnable[] =
{
    MSEHasGuidByte5,
    MSEHasGuidByte4,
    MSEHasGuidByte7,
    MSEHasGuidByte1,
    MSEHasGuidByte3,
    MSEHasGuidByte6,
    MSEHasGuidByte2,
    MSEHasGuidByte0,
    MSEGuidByte7,
    MSEGuidByte3,
    MSEGuidByte4,
    MSEGuidByte2,
    MSEGuidByte1,
    MSEGuidByte6,
    MSEGuidByte0,
    MSEGuidByte5,
    MSEEnd,
};

MovementStatusElements const SplineMoveSetHover[] =
{
    MSEHasGuidByte3,
    MSEHasGuidByte7,
    MSEHasGuidByte0,
    MSEHasGuidByte1,
    MSEHasGuidByte4,
    MSEHasGuidByte6,
    MSEHasGuidByte2,
    MSEHasGuidByte5,
    MSEGuidByte2,
    MSEGuidByte4,
    MSEGuidByte3,
    MSEGuidByte1,
    MSEGuidByte7,
    MSEGuidByte0,
    MSEGuidByte5,
    MSEGuidByte6,
    MSEEnd,
};

MovementStatusElements const SplineMoveUnsetHover[] =
{
    MSEHasGuidByte6,
    MSEHasGuidByte7,
    MSEHasGuidByte4,
    MSEHasGuidByte0,
    MSEHasGuidByte3,
    MSEHasGuidByte1,
    MSEHasGuidByte5,
    MSEHasGuidByte2,
    MSEGuidByte4,
    MSEGuidByte5,
    MSEGuidByte3,
    MSEGuidByte0,
    MSEGuidByte2,
    MSEGuidByte7,
    MSEGuidByte6,
    MSEGuidByte1,
    MSEEnd,
};

MovementStatusElements const SplineMoveStartSwim[] =
{
    MSEHasGuidByte1,
    MSEHasGuidByte6,
    MSEHasGuidByte0,
    MSEHasGuidByte7,
    MSEHasGuidByte3,
    MSEHasGuidByte5,
    MSEHasGuidByte2,
    MSEHasGuidByte4,
    MSEGuidByte3,
    MSEGuidByte7,
    MSEGuidByte2,
    MSEGuidByte5,
    MSEGuidByte6,
    MSEGuidByte4,
    MSEGuidByte1,
    MSEGuidByte0,
    MSEEnd,
};

MovementStatusElements const SplineMoveStopSwim[] =
{
    MSEHasGuidByte4,
    MSEHasGuidByte1,
    MSEHasGuidByte5,
    MSEHasGuidByte3,
    MSEHasGuidByte0,
    MSEHasGuidByte7,
    MSEHasGuidByte2,
    MSEHasGuidByte6,
    MSEGuidByte6,
    MSEGuidByte0,
    MSEGuidByte7,
    MSEGuidByte2,
    MSEGuidByte3,
    MSEGuidByte1,
    MSEGuidByte5,
    MSEGuidByte4,
    MSEEnd,
};

MovementStatusElements const SplineMoveSetFlying[] =
{
    MSEHasGuidByte0,
    MSEHasGuidByte4,
    MSEHasGuidByte1,
    MSEHasGuidByte6,
    MSEHasGuidByte7,
    MSEHasGuidByte2,
    MSEHasGuidByte3,
    MSEHasGuidByte5,
    MSEGuidByte7,
    MSEGuidByte0,
    MSEGuidByte5,
    MSEGuidByte6,
    MSEGuidByte4,
    MSEGuidByte1,
    MSEGuidByte3,
    MSEGuidByte2,
    MSEEnd,
};

MovementStatusElements const SplineMoveUnsetFlying[] =
{
    MSEHasGuidByte5,
    MSEHasGuidByte0,
    MSEHasGuidByte4,
    MSEHasGuidByte7,
    MSEHasGuidByte2,
    MSEHasGuidByte3,
    MSEHasGuidByte1,
    MSEHasGuidByte6,
    MSEGuidByte7,
    MSEGuidByte2,
    MSEGuidByte3,
    MSEGuidByte4,
    MSEGuidByte5,
    MSEGuidByte1,
    MSEGuidByte6,
    MSEGuidByte0,
    MSEEnd,
};

MovementStatusElements const SplineMoveSetWaterWalk[] =
{
    MSEHasGuidByte6,
    MSEHasGuidByte1,
    MSEHasGuidByte4,
    MSEHasGuidByte2,
    MSEHasGuidByte3,
    MSEHasGuidByte7,
    MSEHasGuidByte5,
    MSEHasGuidByte0,
    MSEGuidByte0,
    MSEGuidByte6,
    MSEGuidByte3,
    MSEGuidByte7,
    MSEGuidByte4,
    MSEGuidByte2,
    MSEGuidByte5,
    MSEGuidByte1,
    MSEEnd,
};

MovementStatusElements const SplineMoveSetLandWalk[] =
{
    MSEHasGuidByte5,
    MSEHasGuidByte0,
    MSEHasGuidByte4,
    MSEHasGuidByte6,
    MSEHasGuidByte7,
    MSEHasGuidByte2,
    MSEHasGuidByte3,
    MSEHasGuidByte1,
    MSEGuidByte5,
    MSEGuidByte7,
    MSEGuidByte3,
    MSEGuidByte4,
    MSEGuidByte1,
    MSEGuidByte2,
    MSEGuidByte0,
    MSEGuidByte6,
    MSEEnd,
};

MovementStatusElements const SplineMoveSetFeatherFall[] =
{
    MSEHasGuidByte3,
    MSEHasGuidByte2,
    MSEHasGuidByte7,
    MSEHasGuidByte5,
    MSEHasGuidByte4,
    MSEHasGuidByte6,
    MSEHasGuidByte1,
    MSEHasGuidByte0,
    MSEGuidByte1,
    MSEGuidByte4,
    MSEGuidByte7,
    MSEGuidByte6,
    MSEGuidByte2,
    MSEGuidByte0,
    MSEGuidByte5,
    MSEGuidByte3,
    MSEEnd,
};

MovementStatusElements const SplineMoveSetNormalFall[] =
{
    MSEHasGuidByte3,
    MSEHasGuidByte5,
    MSEHasGuidByte1,
    MSEHasGuidByte0,
    MSEHasGuidByte7,
    MSEHasGuidByte6,
    MSEHasGuidByte2,
    MSEHasGuidByte4,
    MSEGuidByte7,
    MSEGuidByte6,
    MSEGuidByte2,
    MSEGuidByte0,
    MSEGuidByte5,
    MSEGuidByte4,
    MSEGuidByte3,
    MSEGuidByte1,
    MSEEnd,
};

MovementStatusElements const SplineMoveRoot[] =
{
    MSEHasGuidByte5,
    MSEHasGuidByte4,
    MSEHasGuidByte6,
    MSEHasGuidByte1,
    MSEHasGuidByte3,
    MSEHasGuidByte7,
    MSEHasGuidByte2,
    MSEHasGuidByte0,
    MSEGuidByte2,
    MSEGuidByte1,
    MSEGuidByte7,
    MSEGuidByte3,
    MSEGuidByte5,
    MSEGuidByte0,
    MSEGuidByte6,
    MSEGuidByte4,
    MSEEnd,
};

MovementStatusElements const SplineMoveUnroot[] =
{
    MSEHasGuidByte0,
    MSEHasGuidByte1,
    MSEHasGuidByte6,
    MSEHasGuidByte5,
    MSEHasGuidByte3,
    MSEHasGuidByte2,
    MSEHasGuidByte7,
    MSEHasGuidByte4,
    MSEGuidByte6,
    MSEGuidByte3,
    MSEGuidByte1,
    MSEGuidByte5,
    MSEGuidByte2,
    MSEGuidByte0,
    MSEGuidByte7,
    MSEGuidByte4,
    MSEEnd,
};

MovementStatusElements const MoveSetCanFly[] =
{
    MSEHasGuidByte1,
    MSEHasGuidByte6,
    MSEHasGuidByte5,
    MSEHasGuidByte0,
    MSEHasGuidByte7,
    MSEHasGuidByte4,
    MSEHasGuidByte2,
    MSEHasGuidByte3,
    MSEGuidByte6,
    MSEGuidByte3,
    MSECounter,
    MSEGuidByte2,
    MSEGuidByte1,
    MSEGuidByte4,
    MSEGuidByte7,
    MSEGuidByte0,
    MSEGuidByte5,
    MSEEnd,
};

MovementStatusElements const MoveUnsetCanFly[] =
{
    MSEHasGuidByte1,
    MSEHasGuidByte4,
    MSEHasGuidByte2,
    MSEHasGuidByte5,
    MSEHasGuidByte0,
    MSEHasGuidByte3,
    MSEHasGuidByte6,
    MSEHasGuidByte7,
    MSEGuidByte4,
    MSEGuidByte6,
    MSECounter,
    MSEGuidByte1,
    MSEGuidByte0,
    MSEGuidByte2,
    MSEGuidByte3,
    MSEGuidByte5,
    MSEGuidByte7,
    MSEEnd,
};

MovementStatusElements const MoveSetHover[] =
{
    MSEHasGuidByte1,
    MSEHasGuidByte4,
    MSEHasGuidByte2,
    MSEHasGuidByte3,
    MSEHasGuidByte0,
    MSEHasGuidByte5,
    MSEHasGuidByte6,
    MSEHasGuidByte7,
    MSEGuidByte5,
    MSEGuidByte4,
    MSEGuidByte1,
    MSEGuidByte2,
    MSEGuidByte3,
    MSEGuidByte6,
    MSEGuidByte0,
    MSEGuidByte7,
    MSECounter,
    MSEEnd,
};

MovementStatusElements const MoveUnsetHover[] =
{
    MSEHasGuidByte4,
    MSEHasGuidByte6,
    MSEHasGuidByte3,
    MSEHasGuidByte1,
    MSEHasGuidByte2,
    MSEHasGuidByte7,
    MSEHasGuidByte5,
    MSEHasGuidByte0,
    MSEGuidByte4,
    MSEGuidByte5,
    MSEGuidByte3,
    MSEGuidByte6,
    MSEGuidByte7,
    MSEGuidByte1,
    MSEGuidByte2,
    MSEGuidByte0,
    MSECounter,
    MSEEnd,
};

MovementStatusElements const MoveWaterWalk[] =
{
    MSEHasGuidByte4,
    MSEHasGuidByte7,
    MSEHasGuidByte6,
    MSEHasGuidByte0,
    MSEHasGuidByte1,
    MSEHasGuidByte3,
    MSEHasGuidByte5,
    MSEHasGuidByte2,
    MSEGuidByte0,
    MSEGuidByte5,
    MSEGuidByte2,
    MSECounter,
    MSEGuidByte7,
    MSEGuidByte3,
    MSEGuidByte4,
    MSEGuidByte1,
    MSEGuidByte6,
    MSEEnd,
};

MovementStatusElements const MoveLandWalk[] =
{
    MSEHasGuidByte5,
    MSEHasGuidByte1,
    MSEHasGuidByte6,
    MSEHasGuidByte2,
    MSEHasGuidByte3,
    MSEHasGuidByte4,
    MSEHasGuidByte0,
    MSEHasGuidByte7,
    MSEGuidByte6,
    MSEGuidByte1,
    MSEGuidByte7,
    MSEGuidByte5,
    MSEGuidByte4,
    MSEGuidByte0,
    MSEGuidByte3,
    MSEGuidByte2,
    MSECounter,
    MSEEnd,
};

MovementStatusElements const MoveFeatherFall[] =
{
    MSEHasGuidByte3,
    MSEHasGuidByte1,
    MSEHasGuidByte7,
    MSEHasGuidByte0,
    MSEHasGuidByte4,
    MSEHasGuidByte2,
    MSEHasGuidByte5,
    MSEHasGuidByte6,
    MSEGuidByte5,
    MSEGuidByte7,
    MSEGuidByte2,
    MSECounter,
    MSEGuidByte0,
    MSEGuidByte3,
    MSEGuidByte4,
    MSEGuidByte1,
    MSEGuidByte6,
    MSEEnd,
};

MovementStatusElements const MoveNormalFall[] =
{
    MSECounter,
    MSEHasGuidByte3,
    MSEHasGuidByte0,
    MSEHasGuidByte1,
    MSEHasGuidByte5,
    MSEHasGuidByte7,
    MSEHasGuidByte4,
    MSEHasGuidByte6,
    MSEHasGuidByte2,
    MSEGuidByte2,
    MSEGuidByte7,
    MSEGuidByte1,
    MSEGuidByte4,
    MSEGuidByte5,
    MSEGuidByte0,
    MSEGuidByte3,
    MSEGuidByte6,
    MSEEnd,
};

MovementStatusElements const MoveRoot[] =
{
    MSEHasGuidByte2,
    MSEHasGuidByte7,
    MSEHasGuidByte6,
    MSEHasGuidByte0,
    MSEHasGuidByte5,
    MSEHasGuidByte4,
    MSEHasGuidByte1,
    MSEHasGuidByte3,
    MSEGuidByte1,
    MSEGuidByte0,
    MSEGuidByte2,
    MSEGuidByte5,
    MSECounter,
    MSEGuidByte3,
    MSEGuidByte4,
    MSEGuidByte7,
    MSEGuidByte6,
    MSEEnd,
};

MovementStatusElements const MoveUnroot[] =
{
    MSEHasGuidByte0,
    MSEHasGuidByte1,
    MSEHasGuidByte3,
    MSEHasGuidByte7,
    MSEHasGuidByte5,
    MSEHasGuidByte2,
    MSEHasGuidByte4,
    MSEHasGuidByte6,
    MSEGuidByte3,
    MSEGuidByte6,
    MSEGuidByte1,
    MSECounter,
    MSEGuidByte2,
    MSEGuidByte0,
    MSEGuidByte7,
    MSEGuidByte4,
    MSEGuidByte5,
    MSEEnd,
};

MovementStatusElements const ChangeSeatsOnControlledVehicle[] =
{
    MSEPositionY,
    MSEPositionX,
    MSEPositionZ,
    MSEExtraElement,
    MSEHasMovementFlags,
    MSEHasTransportData,
    MSEHasGuidByte2,
    MSEHasGuidByte6,
    MSEHasGuidByte4,
    MSEExtraElement,
    MSEExtraElement,
    MSEHasOrientation,
    MSEZeroBit,
    MSEExtraElement,
    MSEHasGuidByte7,
    MSEExtraElement,
    MSEHasTimestamp,
    MSEHasSplineElevation,
    MSEHasGuidByte5,
    MSEExtraElement,
    MSEHasMovementFlags2,
    MSEHasPitch,
    MSEExtraElement,
    MSEHasGuidByte0,
    MSEExtraElement,
    MSEHasFallData,
    MSEHasGuidByte1,
    MSEHasSpline,
    MSEMovementFlags,
    MSEExtraElement,
    MSEHasGuidByte3,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte5,
    MSEHasVehicleId,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte2,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte6,
    MSEMovementFlags2,
    MSEHasFallDirection,
    MSEExtraElement,
    MSEGuidByte7,
    MSEGuidByte5,
    MSEExtraElement,
    MSEExtraElement,
    MSEGuidByte6,
    MSEExtraElement,
    MSEExtraElement,
    MSEGuidByte3,
    MSEExtraElement,
    MSEGuidByte0,
    MSEExtraElement,
    MSEGuidByte4,
    MSEGuidByte1,
    MSEExtraElement,
    MSEGuidByte2,
    MSEPitch,
    MSEFallCosAngle,
    MSEFallSinAngle,
    MSEFallHorizontalSpeed,
    MSEFallTime,
    MSEFallVerticalSpeed,
    MSETransportGuidByte2,
    MSETransportTime2,
    MSETransportVehicleId,
    MSETransportGuidByte0,
    MSETransportTime,
    MSETransportSeat,
    MSETransportPositionX,
    MSETransportOrientation,
    MSETransportGuidByte7,
    MSETransportGuidByte4,
    MSETransportGuidByte3,
    MSETransportGuidByte5,
    MSETransportPositionZ,
    MSETransportGuidByte1,
    MSETransportGuidByte6,
    MSETransportPositionY,
    MSESplineElevation,
    MSEOrientation,
    MSETimestamp,
    MSEEnd,
};

MovementStatusElements const CastSpellEmbeddedMovement[] =
{
    MSEPositionZ,
    MSEPositionY,
    MSEPositionX,
    MSEHasFallData,
    MSEHasTimestamp,
    MSEHasOrientation,
    MSEZeroBit,
    MSEHasSpline,
    MSEHasGuidByte6,
    MSEHasGuidByte4,
    MSEHasMovementFlags2,
    MSEHasGuidByte3,
    MSEHasGuidByte5,
    MSEHasSplineElevation,
    MSEHasPitch,
    MSEHasGuidByte7,
    MSEHasTransportData,
    MSEHasGuidByte2,
    MSEHasMovementFlags,
    MSEHasGuidByte1,
    MSEHasGuidByte0,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte5,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte4,
    MSEHasVehicleId,
    MSEHasTransportGuidByte0,
    MSEHasTransportGuidByte1,
    MSEHasTransportGuidByte3,
    MSEMovementFlags2,
    MSEMovementFlags,
    MSEHasFallDirection,
    MSEGuidByte1,
    MSEGuidByte4,
    MSEGuidByte7,
    MSEGuidByte3,
    MSEGuidByte0,
    MSEGuidByte2,
    MSEGuidByte5,
    MSEGuidByte6,
    MSETransportSeat,
    MSETransportOrientation,
    MSETransportTime,
    MSETransportGuidByte6,
    MSETransportGuidByte5,
    MSETransportVehicleId,
    MSETransportPositionX,
    MSETransportGuidByte4,
    MSETransportPositionZ,
    MSETransportGuidByte2,
    MSETransportGuidByte0,
    MSETransportTime2,
    MSETransportGuidByte1,
    MSETransportGuidByte3,
    MSETransportPositionY,
    MSETransportGuidByte7,
    MSEOrientation,
    MSESplineElevation,
    MSEFallTime,
    MSEFallHorizontalSpeed,
    MSEFallSinAngle,
    MSEFallCosAngle,
    MSEFallVerticalSpeed,
    MSETimestamp,
    MSEPitch,
    MSEEnd,
};

MovementStatusElements const MoveGravityDisable[] =
{
    MSEHasGuidByte0,
    MSEHasGuidByte1,
    MSEHasGuidByte5,
    MSEHasGuidByte7,
    MSEHasGuidByte6,
    MSEHasGuidByte4,
    MSEHasGuidByte3,
    MSEHasGuidByte2,
    MSEGuidByte7,
    MSEGuidByte2,
    MSEGuidByte0,
    MSECounter,
    MSEGuidByte5,
    MSEGuidByte1,
    MSEGuidByte3,
    MSEGuidByte4,
    MSEGuidByte6,
    MSEEnd,
};

MovementStatusElements const MoveGravityEnable[] =
{
    MSEHasGuidByte1,
    MSEHasGuidByte4,
    MSEHasGuidByte7,
    MSEHasGuidByte5,
    MSEHasGuidByte2,
    MSEHasGuidByte0,
    MSEHasGuidByte3,
    MSEHasGuidByte6,
    MSEGuidByte3,
    MSECounter,
    MSEGuidByte7,
    MSEGuidByte6,
    MSEGuidByte4,
    MSEGuidByte0,
    MSEGuidByte1,
    MSEGuidByte5,
    MSEGuidByte2,
    MSEEnd,
};

MovementStatusElements const MoveUpdateFlightBackSpeed[] =
{
    MSEPositionY,
    MSEExtraElement,
    MSEPositionX,
    MSEPositionZ,
    MSEHasGuidByte6,
    MSEHasGuidByte4,
    MSEHasPitch,
    MSEHasGuidByte7,
    MSEHasGuidByte1,
    MSEHasTransportData,
    MSEHasVehicleId,
    MSEHasTransportGuidByte4,
    MSEHasTransportGuidByte7,
    MSEHasTransportGuidByte6,
    MSEHasTransportGuidByte0,
    MSEOneBit, // has_transport_time
    MSEHasTransportGuidByte2,
    MSEHasTransportGuidByte3,
    MSEHasTransportGuidByte5,
    MSEHasTransportTime2,
    MSEHasTransportGuidByte1,
    MSEHasGuidByte5,
    MSEHasGuidByte0,
    MSEHasTimestamp,
    MSEHasMovementFlags,
    MSEMovementFlags,
    MSEHasGuidByte3,
    MSEHasMovementFlags2,
    MSEZeroBit, // height_change_failed
    MSEHasSplineElevation,
    MSEMovementFlags2,
    MSEHasGuidByte2,
    MSEHasFallData,
    MSEHasOrientation,
    MSEHasFallDirection,
    MSEFlushBits,
    MSEFallCosAngle,
    MSEFallSinAngle,
    MSEFallVerticalSpeed,
    MSEFallTime,
    MSEFallHorizontalSpeed,
    MSETransportPositionX,
    MSETransportTime,
    MSETransportOrientation,
    MSETransportGuidByte5,
    MSETransportPositionZ,
    MSETransportVehicleId,
    MSETransportGuidByte7,
    MSETransportGuidByte1,
    MSETransportGuidByte3,
    MSETransportGuidByte6,
    MSETransportGuidByte0,
    MSETransportGuidByte2,
    MSETransportPositionY,
    MSETransportGuidByte4,
    MSEGuidByte1,
    MSEGuidByte4,
    MSEOrientation,
    MSEGuidByte5,
    MSETimestamp,
    MSESplineElevation,
    MSEGuidByte6,
    MSEPitch,
    MSEGuidByte3,
    MSEGuidByte2,
    MSEGuidByte0,
    MSEGuidByte7,
    MSEEnd
};

MovementStatusElements const MoveSetCanTransitionBetweenSwimAndFly[] =
{
    MSEHasGuidByte4,
    MSEHasGuidByte5,
    MSEHasGuidByte7,
    MSEHasGuidByte0,
    MSEHasGuidByte2,
    MSEHasGuidByte6,
    MSEHasGuidByte1,
    MSEHasGuidByte3,
    MSEGuidByte0,
    MSEGuidByte6,
    MSEGuidByte1,
    MSEGuidByte2,
    MSEGuidByte5,
    MSEGuidByte4,
    MSEGuidByte7,
    MSECounter,
    MSEGuidByte3,
    MSEEnd,
};

MovementStatusElements const MoveUnsetCanTransitionBetweenSwimAndFly[] =
{
    MSEHasGuidByte3,
    MSEHasGuidByte4,
    MSEHasGuidByte7,
    MSEHasGuidByte0,
    MSEHasGuidByte6,
    MSEHasGuidByte1,
    MSEHasGuidByte5,
    MSEHasGuidByte2,
    MSEGuidByte5,
    MSEGuidByte2,
    MSEGuidByte7,
    MSEGuidByte0,
    MSECounter,
    MSEGuidByte6,
    MSEGuidByte4,
    MSEGuidByte3,
    MSEGuidByte1,
    MSEEnd,
};

void Cataclysm::ExtraMovementStatusElement::ReadNextElement(ByteBuffer& packet)
{
    MovementStatusElements const element = _elements[_index++];

    switch (element)
    {
        case MSEHasGuidByte0:
        case MSEHasGuidByte1:
        case MSEHasGuidByte2:
        case MSEHasGuidByte3:
        case MSEHasGuidByte4:
        case MSEHasGuidByte5:
        case MSEHasGuidByte6:
        case MSEHasGuidByte7:
            Data.guid[element - MSEHasGuidByte0] = packet.ReadBit();
            break;
        case MSEGuidByte0:
        case MSEGuidByte1:
        case MSEGuidByte2:
        case MSEGuidByte3:
        case MSEGuidByte4:
        case MSEGuidByte5:
        case MSEGuidByte6:
        case MSEGuidByte7:
            packet.ReadByteSeq(Data.guid[element - MSEGuidByte0]);
            break;
        case MSEExtraFloat:
            packet >> Data.floatData;
            break;
        case MSEExtraInt8:
            packet >> Data.byteData;
            break;
        case MSEExtraTwoBits:
            Data.byteData = packet.ReadBits(2);
            break;
        default:
            printf("[ERROR] ExtraMovementStatusElement::ReadNextElement Incorrect sequence element %u detected", element);
            break;
    }
}

void Cataclysm::ExtraMovementStatusElement::WriteNextElement(ByteBuffer& packet)
{
    MovementStatusElements const element = _elements[_index++];

    switch (element)
    {
        case MSEHasGuidByte0:
        case MSEHasGuidByte1:
        case MSEHasGuidByte2:
        case MSEHasGuidByte3:
        case MSEHasGuidByte4:
        case MSEHasGuidByte5:
        case MSEHasGuidByte6:
        case MSEHasGuidByte7:
            packet.WriteBit(Data.guid[element - MSEHasGuidByte0]);
            break;
        case MSEGuidByte0:
        case MSEGuidByte1:
        case MSEGuidByte2:
        case MSEGuidByte3:
        case MSEGuidByte4:
        case MSEGuidByte5:
        case MSEGuidByte6:
        case MSEGuidByte7:
            packet.WriteByteSeq(Data.guid[element - MSEGuidByte0]);
            break;
        case MSEExtraFloat:
            packet << Data.floatData;
            break;
        case MSEExtraInt8:
            packet << Data.byteData;
            break;
        case MSEExtraTwoBits:
            packet.WriteBits(Data.byteData, 2);
            break;
        default:
            printf("[ERROR] ExtraMovementStatusElement::WriteNextElement Incorrect sequence element %u detected", element);
            break;
    }
}

uint16 MSG_MOVE_FALL_LAND;
uint16 MSG_MOVE_HEARTBEAT;
uint16 MSG_MOVE_JUMP;
uint16 MSG_MOVE_SET_FACING;
uint16 MSG_MOVE_SET_PITCH;
uint16 MSG_MOVE_START_ASCEND;
uint16 MSG_MOVE_START_BACKWARD;
uint16 MSG_MOVE_START_DESCEND;
uint16 MSG_MOVE_START_FORWARD;
uint16 MSG_MOVE_START_PITCH_DOWN;
uint16 MSG_MOVE_START_PITCH_UP;
uint16 MSG_MOVE_START_STRAFE_LEFT;
uint16 MSG_MOVE_START_STRAFE_RIGHT;
uint16 MSG_MOVE_START_SWIM;
uint16 MSG_MOVE_START_TURN_LEFT;
uint16 MSG_MOVE_START_TURN_RIGHT;
uint16 MSG_MOVE_STOP;
uint16 MSG_MOVE_STOP_ASCEND;
uint16 MSG_MOVE_STOP_PITCH;
uint16 MSG_MOVE_STOP_STRAFE;
uint16 MSG_MOVE_STOP_SWIM;
uint16 MSG_MOVE_STOP_TURN;
uint16 CMSG_MOVE_CHNG_TRANSPORT;
uint16 CMSG_MOVE_SPLINE_DONE;
uint16 CMSG_MOVE_NOT_ACTIVE_MOVER;
uint16 CMSG_DISMISS_CONTROLLED_VEHICLE;
uint16 CMSG_FORCE_MOVE_ROOT_ACK;
uint16 CMSG_FORCE_MOVE_UNROOT_ACK;
uint16 CMSG_MOVE_FALL_RESET;
uint16 CMSG_MOVE_FEATHER_FALL_ACK;
uint16 CMSG_MOVE_FORCE_FLIGHT_SPEED_CHANGE_ACK;
uint16 CMSG_MOVE_FORCE_RUN_BACK_SPEED_CHANGE_ACK;
uint16 CMSG_MOVE_FORCE_RUN_SPEED_CHANGE_ACK;
uint16 CMSG_MOVE_FORCE_SWIM_SPEED_CHANGE_ACK;
uint16 CMSG_MOVE_FORCE_SWIM_BACK_SPEED_CHANGE_ACK;
uint16 CMSG_MOVE_FORCE_FLIGHT_BACK_SPEED_CHANGE_ACK;
uint16 CMSG_MOVE_FORCE_WALK_SPEED_CHANGE_ACK;
uint16 CMSG_MOVE_GRAVITY_DISABLE_ACK;
uint16 CMSG_MOVE_GRAVITY_ENABLE_ACK;
uint16 CMSG_MOVE_HOVER_ACK;
uint16 CMSG_MOVE_KNOCK_BACK_ACK;
uint16 CMSG_MOVE_SET_CAN_FLY;
uint16 CMSG_MOVE_SET_CAN_FLY_ACK;
uint16 CMSG_MOVE_SET_CAN_TRANSITION_BETWEEN_SWIM_AND_FLY_ACK;
uint16 CMSG_MOVE_SET_COLLISION_HEIGHT_ACK;
uint16 SMSG_MOVE_SET_COLLISION_HEIGHT;
uint16 SMSG_MOVE_UPDATE_COLLISION_HEIGHT;
uint16 CMSG_MOVE_WATER_WALK_ACK;
uint16 MSG_MOVE_SET_RUN_MODE;
uint16 MSG_MOVE_SET_WALK_MODE;
uint16 SMSG_MOVE_UPDATE;
uint16 SMSG_MOVE_UPDATE_FLIGHT_SPEED;
uint16 SMSG_MOVE_UPDATE_RUN_SPEED;
uint16 SMSG_MOVE_UPDATE_KNOCK_BACK;
uint16 SMSG_MOVE_UPDATE_RUN_BACK_SPEED;
uint16 SMSG_MOVE_UPDATE_SWIM_SPEED;
uint16 SMSG_MOVE_UPDATE_SWIM_BACK_SPEED;
uint16 SMSG_MOVE_UPDATE_WALK_SPEED;
uint16 SMSG_SPLINE_MOVE_SET_WALK_SPEED;
uint16 SMSG_SPLINE_MOVE_SET_RUN_SPEED;
uint16 SMSG_SPLINE_MOVE_SET_RUN_BACK_SPEED;
uint16 SMSG_SPLINE_MOVE_SET_SWIM_SPEED;
uint16 SMSG_SPLINE_MOVE_SET_SWIM_BACK_SPEED;
uint16 SMSG_SPLINE_MOVE_SET_TURN_RATE;
uint16 SMSG_SPLINE_MOVE_SET_FLIGHT_SPEED;
uint16 SMSG_SPLINE_MOVE_SET_FLIGHT_BACK_SPEED;
uint16 SMSG_SPLINE_MOVE_SET_PITCH_RATE;
uint16 SMSG_MOVE_SET_WALK_SPEED;
uint16 SMSG_MOVE_SET_RUN_SPEED;
uint16 SMSG_MOVE_SET_RUN_BACK_SPEED;
uint16 SMSG_MOVE_SET_SWIM_SPEED;
uint16 SMSG_MOVE_SET_SWIM_BACK_SPEED;
uint16 SMSG_MOVE_SET_TURN_RATE;
uint16 SMSG_MOVE_SET_FLIGHT_SPEED;
uint16 SMSG_MOVE_SET_FLIGHT_BACK_SPEED;
uint16 SMSG_MOVE_SET_PITCH_RATE;
uint16 SMSG_SPLINE_MOVE_SET_WALK_MODE;
uint16 SMSG_SPLINE_MOVE_SET_RUN_MODE;
uint16 SMSG_SPLINE_MOVE_GRAVITY_DISABLE;
uint16 SMSG_SPLINE_MOVE_GRAVITY_ENABLE;
uint16 SMSG_SPLINE_MOVE_SET_HOVER;
uint16 SMSG_SPLINE_MOVE_UNSET_HOVER;
uint16 SMSG_SPLINE_MOVE_START_SWIM;
uint16 SMSG_SPLINE_MOVE_STOP_SWIM;
uint16 SMSG_SPLINE_MOVE_SET_FLYING;
uint16 SMSG_SPLINE_MOVE_UNSET_FLYING;
uint16 SMSG_SPLINE_MOVE_SET_WATER_WALK;
uint16 SMSG_SPLINE_MOVE_SET_LAND_WALK;
uint16 SMSG_SPLINE_MOVE_SET_FEATHER_FALL;
uint16 SMSG_SPLINE_MOVE_SET_NORMAL_FALL;
uint16 SMSG_SPLINE_MOVE_ROOT;
uint16 SMSG_SPLINE_MOVE_UNROOT;
uint16 SMSG_MOVE_SET_CAN_FLY;
uint16 SMSG_MOVE_UNSET_CAN_FLY;
uint16 SMSG_MOVE_SET_HOVER;
uint16 SMSG_MOVE_UNSET_HOVER;
uint16 SMSG_MOVE_WATER_WALK;
uint16 SMSG_MOVE_LAND_WALK;
uint16 SMSG_MOVE_FEATHER_FALL;
uint16 SMSG_MOVE_NORMAL_FALL;
uint16 SMSG_MOVE_ROOT;
uint16 SMSG_MOVE_UNROOT;
uint16 CMSG_CHANGE_SEATS_ON_CONTROLLED_VEHICLE;
uint16 CMSG_CAST_SPELL;
uint16 CMSG_PET_CAST_SPELL;
uint16 CMSG_USE_ITEM;
uint16 SMSG_MOVE_GRAVITY_DISABLE;
uint16 SMSG_MOVE_GRAVITY_ENABLE;
uint16 SMSG_MOVE_UPDATE_FLIGHT_BACK_SPEED;
uint16 SMSG_MOVE_SET_CAN_TRANSITION_BETWEEN_SWIM_AND_FLY;
uint16 SMSG_MOVE_UNSET_CAN_TRANSITION_BETWEEN_SWIM_AND_FLY;

void CacheMovementOpcodes()
{
    MSG_MOVE_FALL_LAND = Opcodes::GetOpcodeValue("MSG_MOVE_FALL_LAND", sWorld.GetClientBuild());
    MSG_MOVE_HEARTBEAT = Opcodes::GetOpcodeValue("MSG_MOVE_HEARTBEAT", sWorld.GetClientBuild());
    MSG_MOVE_JUMP = Opcodes::GetOpcodeValue("MSG_MOVE_JUMP", sWorld.GetClientBuild());
    MSG_MOVE_SET_FACING = Opcodes::GetOpcodeValue("MSG_MOVE_SET_FACING", sWorld.GetClientBuild());
    MSG_MOVE_SET_PITCH = Opcodes::GetOpcodeValue("MSG_MOVE_SET_PITCH", sWorld.GetClientBuild());
    MSG_MOVE_START_ASCEND = Opcodes::GetOpcodeValue("MSG_MOVE_START_ASCEND", sWorld.GetClientBuild());
    MSG_MOVE_START_BACKWARD = Opcodes::GetOpcodeValue("MSG_MOVE_START_BACKWARD", sWorld.GetClientBuild());
    MSG_MOVE_START_DESCEND = Opcodes::GetOpcodeValue("MSG_MOVE_START_DESCEND", sWorld.GetClientBuild());
    MSG_MOVE_START_FORWARD = Opcodes::GetOpcodeValue("MSG_MOVE_START_FORWARD", sWorld.GetClientBuild());
    MSG_MOVE_START_PITCH_DOWN = Opcodes::GetOpcodeValue("MSG_MOVE_START_PITCH_DOWN", sWorld.GetClientBuild());
    MSG_MOVE_START_PITCH_UP = Opcodes::GetOpcodeValue("MSG_MOVE_START_PITCH_UP", sWorld.GetClientBuild());
    MSG_MOVE_START_STRAFE_LEFT = Opcodes::GetOpcodeValue("MSG_MOVE_START_STRAFE_LEFT", sWorld.GetClientBuild());
    MSG_MOVE_START_STRAFE_RIGHT = Opcodes::GetOpcodeValue("MSG_MOVE_START_STRAFE_RIGHT", sWorld.GetClientBuild());
    MSG_MOVE_START_SWIM = Opcodes::GetOpcodeValue("MSG_MOVE_START_SWIM", sWorld.GetClientBuild());
    MSG_MOVE_START_TURN_LEFT = Opcodes::GetOpcodeValue("MSG_MOVE_START_TURN_LEFT", sWorld.GetClientBuild());
    MSG_MOVE_START_TURN_RIGHT = Opcodes::GetOpcodeValue("MSG_MOVE_START_TURN_RIGHT", sWorld.GetClientBuild());
    MSG_MOVE_STOP = Opcodes::GetOpcodeValue("MSG_MOVE_STOP", sWorld.GetClientBuild());
    MSG_MOVE_STOP_ASCEND = Opcodes::GetOpcodeValue("MSG_MOVE_STOP_ASCEND", sWorld.GetClientBuild());
    MSG_MOVE_STOP_PITCH = Opcodes::GetOpcodeValue("MSG_MOVE_STOP_PITCH", sWorld.GetClientBuild());
    MSG_MOVE_STOP_STRAFE = Opcodes::GetOpcodeValue("MSG_MOVE_STOP_STRAFE", sWorld.GetClientBuild());
    MSG_MOVE_STOP_SWIM = Opcodes::GetOpcodeValue("MSG_MOVE_STOP_SWIM", sWorld.GetClientBuild());
    MSG_MOVE_STOP_TURN = Opcodes::GetOpcodeValue("MSG_MOVE_STOP_TURN", sWorld.GetClientBuild());
    CMSG_MOVE_CHNG_TRANSPORT = Opcodes::GetOpcodeValue("CMSG_MOVE_CHNG_TRANSPORT", sWorld.GetClientBuild());
    CMSG_MOVE_SPLINE_DONE = Opcodes::GetOpcodeValue("CMSG_MOVE_SPLINE_DONE", sWorld.GetClientBuild());
    CMSG_MOVE_NOT_ACTIVE_MOVER = Opcodes::GetOpcodeValue("CMSG_MOVE_NOT_ACTIVE_MOVER", sWorld.GetClientBuild());
    CMSG_DISMISS_CONTROLLED_VEHICLE = Opcodes::GetOpcodeValue("CMSG_DISMISS_CONTROLLED_VEHICLE", sWorld.GetClientBuild());
    CMSG_FORCE_MOVE_ROOT_ACK = Opcodes::GetOpcodeValue("CMSG_FORCE_MOVE_ROOT_ACK", sWorld.GetClientBuild());
    CMSG_FORCE_MOVE_UNROOT_ACK = Opcodes::GetOpcodeValue("CMSG_FORCE_MOVE_UNROOT_ACK", sWorld.GetClientBuild());
    CMSG_MOVE_FALL_RESET = Opcodes::GetOpcodeValue("CMSG_MOVE_FALL_RESET", sWorld.GetClientBuild());
    CMSG_MOVE_FEATHER_FALL_ACK = Opcodes::GetOpcodeValue("CMSG_MOVE_FEATHER_FALL_ACK", sWorld.GetClientBuild());
    CMSG_MOVE_FORCE_FLIGHT_SPEED_CHANGE_ACK = Opcodes::GetOpcodeValue("CMSG_MOVE_FORCE_FLIGHT_SPEED_CHANGE_ACK", sWorld.GetClientBuild());
    CMSG_MOVE_FORCE_RUN_BACK_SPEED_CHANGE_ACK = Opcodes::GetOpcodeValue("CMSG_MOVE_FORCE_RUN_BACK_SPEED_CHANGE_ACK", sWorld.GetClientBuild());
    CMSG_MOVE_FORCE_RUN_SPEED_CHANGE_ACK = Opcodes::GetOpcodeValue("CMSG_MOVE_FORCE_RUN_SPEED_CHANGE_ACK", sWorld.GetClientBuild());
    CMSG_MOVE_FORCE_SWIM_SPEED_CHANGE_ACK = Opcodes::GetOpcodeValue("CMSG_MOVE_FORCE_SWIM_SPEED_CHANGE_ACK", sWorld.GetClientBuild());
    CMSG_MOVE_FORCE_SWIM_BACK_SPEED_CHANGE_ACK = Opcodes::GetOpcodeValue("CMSG_MOVE_FORCE_SWIM_BACK_SPEED_CHANGE_ACK", sWorld.GetClientBuild());
    CMSG_MOVE_FORCE_FLIGHT_BACK_SPEED_CHANGE_ACK = Opcodes::GetOpcodeValue("CMSG_MOVE_FORCE_FLIGHT_BACK_SPEED_CHANGE_ACK", sWorld.GetClientBuild());
    CMSG_MOVE_FORCE_WALK_SPEED_CHANGE_ACK = Opcodes::GetOpcodeValue("CMSG_MOVE_FORCE_WALK_SPEED_CHANGE_ACK", sWorld.GetClientBuild());
    CMSG_MOVE_GRAVITY_DISABLE_ACK = Opcodes::GetOpcodeValue("CMSG_MOVE_GRAVITY_DISABLE_ACK", sWorld.GetClientBuild());
    CMSG_MOVE_GRAVITY_ENABLE_ACK = Opcodes::GetOpcodeValue("CMSG_MOVE_GRAVITY_ENABLE_ACK", sWorld.GetClientBuild());
    CMSG_MOVE_HOVER_ACK = Opcodes::GetOpcodeValue("CMSG_MOVE_HOVER_ACK", sWorld.GetClientBuild());
    CMSG_MOVE_KNOCK_BACK_ACK = Opcodes::GetOpcodeValue("CMSG_MOVE_KNOCK_BACK_ACK", sWorld.GetClientBuild());
    CMSG_MOVE_SET_CAN_FLY = Opcodes::GetOpcodeValue("CMSG_MOVE_SET_CAN_FLY", sWorld.GetClientBuild());
    CMSG_MOVE_SET_CAN_FLY_ACK = Opcodes::GetOpcodeValue("CMSG_MOVE_SET_CAN_FLY_ACK", sWorld.GetClientBuild());
    CMSG_MOVE_SET_CAN_TRANSITION_BETWEEN_SWIM_AND_FLY_ACK = Opcodes::GetOpcodeValue("CMSG_MOVE_SET_CAN_TRANSITION_BETWEEN_SWIM_AND_FLY_ACK", sWorld.GetClientBuild());
    CMSG_MOVE_SET_COLLISION_HEIGHT_ACK = Opcodes::GetOpcodeValue("CMSG_MOVE_SET_COLLISION_HEIGHT_ACK", sWorld.GetClientBuild());
    SMSG_MOVE_SET_COLLISION_HEIGHT = Opcodes::GetOpcodeValue("SMSG_MOVE_SET_COLLISION_HEIGHT", sWorld.GetClientBuild());
    SMSG_MOVE_UPDATE_COLLISION_HEIGHT = Opcodes::GetOpcodeValue("SMSG_MOVE_UPDATE_COLLISION_HEIGHT", sWorld.GetClientBuild());
    CMSG_MOVE_WATER_WALK_ACK = Opcodes::GetOpcodeValue("CMSG_MOVE_WATER_WALK_ACK", sWorld.GetClientBuild());
    MSG_MOVE_SET_RUN_MODE = Opcodes::GetOpcodeValue("MSG_MOVE_SET_RUN_MODE", sWorld.GetClientBuild());
    MSG_MOVE_SET_WALK_MODE = Opcodes::GetOpcodeValue("MSG_MOVE_SET_WALK_MODE", sWorld.GetClientBuild());
    SMSG_MOVE_UPDATE = Opcodes::GetOpcodeValue("SMSG_MOVE_UPDATE", sWorld.GetClientBuild());
    SMSG_MOVE_UPDATE_FLIGHT_SPEED = Opcodes::GetOpcodeValue("SMSG_MOVE_UPDATE_FLIGHT_SPEED", sWorld.GetClientBuild());
    SMSG_MOVE_UPDATE_RUN_SPEED = Opcodes::GetOpcodeValue("SMSG_MOVE_UPDATE_RUN_SPEED", sWorld.GetClientBuild());
    SMSG_MOVE_UPDATE_KNOCK_BACK = Opcodes::GetOpcodeValue("SMSG_MOVE_UPDATE_KNOCK_BACK", sWorld.GetClientBuild());
    SMSG_MOVE_UPDATE_RUN_BACK_SPEED = Opcodes::GetOpcodeValue("SMSG_MOVE_UPDATE_RUN_BACK_SPEED", sWorld.GetClientBuild());
    SMSG_MOVE_UPDATE_SWIM_SPEED = Opcodes::GetOpcodeValue("SMSG_MOVE_UPDATE_SWIM_SPEED", sWorld.GetClientBuild());
    SMSG_MOVE_UPDATE_SWIM_BACK_SPEED = Opcodes::GetOpcodeValue("SMSG_MOVE_UPDATE_SWIM_BACK_SPEED", sWorld.GetClientBuild());
    SMSG_MOVE_UPDATE_WALK_SPEED = Opcodes::GetOpcodeValue("SMSG_MOVE_UPDATE_WALK_SPEED", sWorld.GetClientBuild());
    SMSG_SPLINE_MOVE_SET_WALK_SPEED = Opcodes::GetOpcodeValue("SMSG_SPLINE_MOVE_SET_WALK_SPEED", sWorld.GetClientBuild());
    SMSG_SPLINE_MOVE_SET_RUN_SPEED = Opcodes::GetOpcodeValue("SMSG_SPLINE_MOVE_SET_RUN_SPEED", sWorld.GetClientBuild());
    SMSG_SPLINE_MOVE_SET_RUN_BACK_SPEED = Opcodes::GetOpcodeValue("SMSG_SPLINE_MOVE_SET_RUN_BACK_SPEED", sWorld.GetClientBuild());
    SMSG_SPLINE_MOVE_SET_SWIM_SPEED = Opcodes::GetOpcodeValue("SMSG_SPLINE_MOVE_SET_SWIM_SPEED", sWorld.GetClientBuild());
    SMSG_SPLINE_MOVE_SET_SWIM_BACK_SPEED = Opcodes::GetOpcodeValue("SMSG_SPLINE_MOVE_SET_SWIM_BACK_SPEED", sWorld.GetClientBuild());
    SMSG_SPLINE_MOVE_SET_TURN_RATE = Opcodes::GetOpcodeValue("SMSG_SPLINE_MOVE_SET_TURN_RATE", sWorld.GetClientBuild());
    SMSG_SPLINE_MOVE_SET_FLIGHT_SPEED = Opcodes::GetOpcodeValue("SMSG_SPLINE_MOVE_SET_FLIGHT_SPEED", sWorld.GetClientBuild());
    SMSG_SPLINE_MOVE_SET_FLIGHT_BACK_SPEED = Opcodes::GetOpcodeValue("SMSG_SPLINE_MOVE_SET_FLIGHT_BACK_SPEED", sWorld.GetClientBuild());
    SMSG_SPLINE_MOVE_SET_PITCH_RATE = Opcodes::GetOpcodeValue("SMSG_SPLINE_MOVE_SET_PITCH_RATE", sWorld.GetClientBuild());
    SMSG_MOVE_SET_WALK_SPEED = Opcodes::GetOpcodeValue("SMSG_MOVE_SET_WALK_SPEED", sWorld.GetClientBuild());
    SMSG_MOVE_SET_RUN_SPEED = Opcodes::GetOpcodeValue("SMSG_MOVE_SET_RUN_SPEED", sWorld.GetClientBuild());
    SMSG_MOVE_SET_RUN_BACK_SPEED = Opcodes::GetOpcodeValue("SMSG_MOVE_SET_RUN_BACK_SPEED", sWorld.GetClientBuild());
    SMSG_MOVE_SET_SWIM_SPEED = Opcodes::GetOpcodeValue("SMSG_MOVE_SET_SWIM_SPEED", sWorld.GetClientBuild());
    SMSG_MOVE_SET_SWIM_BACK_SPEED = Opcodes::GetOpcodeValue("SMSG_MOVE_SET_SWIM_BACK_SPEED", sWorld.GetClientBuild());
    SMSG_MOVE_SET_TURN_RATE = Opcodes::GetOpcodeValue("SMSG_MOVE_SET_TURN_RATE", sWorld.GetClientBuild());
    SMSG_MOVE_SET_FLIGHT_SPEED = Opcodes::GetOpcodeValue("SMSG_MOVE_SET_FLIGHT_SPEED", sWorld.GetClientBuild());
    SMSG_MOVE_SET_FLIGHT_BACK_SPEED = Opcodes::GetOpcodeValue("SMSG_MOVE_SET_FLIGHT_BACK_SPEED", sWorld.GetClientBuild());
    SMSG_MOVE_SET_PITCH_RATE = Opcodes::GetOpcodeValue("SMSG_MOVE_SET_PITCH_RATE", sWorld.GetClientBuild());
    SMSG_SPLINE_MOVE_SET_WALK_MODE = Opcodes::GetOpcodeValue("SMSG_SPLINE_MOVE_SET_WALK_MODE", sWorld.GetClientBuild());
    SMSG_SPLINE_MOVE_SET_RUN_MODE = Opcodes::GetOpcodeValue("SMSG_SPLINE_MOVE_SET_RUN_MODE", sWorld.GetClientBuild());
    SMSG_SPLINE_MOVE_GRAVITY_DISABLE = Opcodes::GetOpcodeValue("SMSG_SPLINE_MOVE_GRAVITY_DISABLE", sWorld.GetClientBuild());
    SMSG_SPLINE_MOVE_GRAVITY_ENABLE = Opcodes::GetOpcodeValue("SMSG_SPLINE_MOVE_GRAVITY_ENABLE", sWorld.GetClientBuild());
    SMSG_SPLINE_MOVE_SET_HOVER = Opcodes::GetOpcodeValue("SMSG_SPLINE_MOVE_SET_HOVER", sWorld.GetClientBuild());
    SMSG_SPLINE_MOVE_UNSET_HOVER = Opcodes::GetOpcodeValue("SMSG_SPLINE_MOVE_UNSET_HOVER", sWorld.GetClientBuild());
    SMSG_SPLINE_MOVE_START_SWIM = Opcodes::GetOpcodeValue("SMSG_SPLINE_MOVE_START_SWIM", sWorld.GetClientBuild());
    SMSG_SPLINE_MOVE_STOP_SWIM = Opcodes::GetOpcodeValue("SMSG_SPLINE_MOVE_STOP_SWIM", sWorld.GetClientBuild());
    SMSG_SPLINE_MOVE_SET_FLYING = Opcodes::GetOpcodeValue("SMSG_SPLINE_MOVE_SET_FLYING", sWorld.GetClientBuild());
    SMSG_SPLINE_MOVE_UNSET_FLYING = Opcodes::GetOpcodeValue("SMSG_SPLINE_MOVE_UNSET_FLYING", sWorld.GetClientBuild());
    SMSG_SPLINE_MOVE_SET_WATER_WALK = Opcodes::GetOpcodeValue("SMSG_SPLINE_MOVE_SET_WATER_WALK", sWorld.GetClientBuild());
    SMSG_SPLINE_MOVE_SET_LAND_WALK = Opcodes::GetOpcodeValue("SMSG_SPLINE_MOVE_SET_LAND_WALK", sWorld.GetClientBuild());
    SMSG_SPLINE_MOVE_SET_FEATHER_FALL = Opcodes::GetOpcodeValue("SMSG_SPLINE_MOVE_SET_FEATHER_FALL", sWorld.GetClientBuild());
    SMSG_SPLINE_MOVE_SET_NORMAL_FALL = Opcodes::GetOpcodeValue("SMSG_SPLINE_MOVE_SET_NORMAL_FALL", sWorld.GetClientBuild());
    SMSG_SPLINE_MOVE_ROOT = Opcodes::GetOpcodeValue("SMSG_SPLINE_MOVE_ROOT", sWorld.GetClientBuild());
    SMSG_SPLINE_MOVE_UNROOT = Opcodes::GetOpcodeValue("SMSG_SPLINE_MOVE_UNROOT", sWorld.GetClientBuild());
    SMSG_MOVE_SET_CAN_FLY = Opcodes::GetOpcodeValue("SMSG_MOVE_SET_CAN_FLY", sWorld.GetClientBuild());
    SMSG_MOVE_UNSET_CAN_FLY = Opcodes::GetOpcodeValue("SMSG_MOVE_UNSET_CAN_FLY", sWorld.GetClientBuild());
    SMSG_MOVE_SET_HOVER = Opcodes::GetOpcodeValue("SMSG_MOVE_SET_HOVER", sWorld.GetClientBuild());
    SMSG_MOVE_UNSET_HOVER = Opcodes::GetOpcodeValue("SMSG_MOVE_UNSET_HOVER", sWorld.GetClientBuild());
    SMSG_MOVE_WATER_WALK = Opcodes::GetOpcodeValue("SMSG_MOVE_WATER_WALK", sWorld.GetClientBuild());
    SMSG_MOVE_LAND_WALK = Opcodes::GetOpcodeValue("SMSG_MOVE_LAND_WALK", sWorld.GetClientBuild());
    SMSG_MOVE_FEATHER_FALL = Opcodes::GetOpcodeValue("SMSG_MOVE_FEATHER_FALL", sWorld.GetClientBuild());
    SMSG_MOVE_NORMAL_FALL = Opcodes::GetOpcodeValue("SMSG_MOVE_NORMAL_FALL", sWorld.GetClientBuild());
    SMSG_MOVE_ROOT = Opcodes::GetOpcodeValue("SMSG_MOVE_ROOT", sWorld.GetClientBuild());
    SMSG_MOVE_UNROOT = Opcodes::GetOpcodeValue("SMSG_MOVE_UNROOT", sWorld.GetClientBuild());
    CMSG_CHANGE_SEATS_ON_CONTROLLED_VEHICLE = Opcodes::GetOpcodeValue("CMSG_CHANGE_SEATS_ON_CONTROLLED_VEHICLE", sWorld.GetClientBuild());
    CMSG_CAST_SPELL = Opcodes::GetOpcodeValue("CMSG_CAST_SPELL", sWorld.GetClientBuild());
    CMSG_PET_CAST_SPELL = Opcodes::GetOpcodeValue("CMSG_PET_CAST_SPELL", sWorld.GetClientBuild());
    CMSG_USE_ITEM = Opcodes::GetOpcodeValue("CMSG_USE_ITEM", sWorld.GetClientBuild());
    SMSG_MOVE_GRAVITY_DISABLE = Opcodes::GetOpcodeValue("SMSG_MOVE_GRAVITY_DISABLE", sWorld.GetClientBuild());
    SMSG_MOVE_GRAVITY_ENABLE = Opcodes::GetOpcodeValue("SMSG_MOVE_GRAVITY_ENABLE", sWorld.GetClientBuild());
    SMSG_MOVE_UPDATE_FLIGHT_BACK_SPEED = Opcodes::GetOpcodeValue("SMSG_MOVE_UPDATE_FLIGHT_BACK_SPEED", sWorld.GetClientBuild());
    SMSG_MOVE_SET_CAN_TRANSITION_BETWEEN_SWIM_AND_FLY = Opcodes::GetOpcodeValue("SMSG_MOVE_SET_CAN_TRANSITION_BETWEEN_SWIM_AND_FLY", sWorld.GetClientBuild());
    SMSG_MOVE_UNSET_CAN_TRANSITION_BETWEEN_SWIM_AND_FLY = Opcodes::GetOpcodeValue("SMSG_MOVE_UNSET_CAN_TRANSITION_BETWEEN_SWIM_AND_FLY", sWorld.GetClientBuild());
}

MovementStatusElements const* Cataclysm::GetMovementStatusElementsSequence(uint32 opcode)
{
    static bool cached = false;
    if (!cached)
    {
        CacheMovementOpcodes();
        cached = true;
    }

    if (opcode == MSG_MOVE_FALL_LAND)
        return MovementFallLand;
    if (opcode == MSG_MOVE_HEARTBEAT)
        return MovementHeartBeat;
    if (opcode == MSG_MOVE_JUMP)
        return MovementJump;
    if (opcode == MSG_MOVE_SET_FACING)
        return MovementSetFacing;
    if (opcode == MSG_MOVE_SET_PITCH)
        return MovementSetPitch;
    if (opcode == MSG_MOVE_START_ASCEND)
        return MovementStartAscend;
    if (opcode == MSG_MOVE_START_BACKWARD)
        return MovementStartBackward;
    if (opcode == MSG_MOVE_START_DESCEND)
        return MovementStartDescend;
    if (opcode == MSG_MOVE_START_FORWARD)
        return MovementStartForward;
    if (opcode == MSG_MOVE_START_PITCH_DOWN)
        return MovementStartPitchDown;
    if (opcode == MSG_MOVE_START_PITCH_UP)
        return MovementStartPitchUp;
    if (opcode == MSG_MOVE_START_STRAFE_LEFT)
        return MovementStartStrafeLeft;
    if (opcode == MSG_MOVE_START_STRAFE_RIGHT)
        return MovementStartStrafeRight;
    if (opcode == MSG_MOVE_START_SWIM)
        return MovementStartSwim;
    if (opcode == MSG_MOVE_START_TURN_LEFT)
        return MovementStartTurnLeft;
    if (opcode == MSG_MOVE_START_TURN_RIGHT)
        return MovementStartTurnRight;
    if (opcode == MSG_MOVE_STOP)
        return MovementStop;
    if (opcode == MSG_MOVE_STOP_ASCEND)
        return MovementStopAscend;
    if (opcode == MSG_MOVE_STOP_PITCH)
        return MovementStopPitch;
    if (opcode == MSG_MOVE_STOP_STRAFE)
        return MovementStopStrafe;
    if (opcode == MSG_MOVE_STOP_SWIM)
        return MovementStopSwim;
    if (opcode == MSG_MOVE_STOP_TURN)
        return MovementStopTurn;
    if (opcode == CMSG_MOVE_CHNG_TRANSPORT)
        return MoveChngTransport;
    if (opcode == CMSG_MOVE_SPLINE_DONE)
        return MoveSplineDone;
    if (opcode == CMSG_MOVE_NOT_ACTIVE_MOVER)
        return MoveNotActiveMover;
    if (opcode == CMSG_DISMISS_CONTROLLED_VEHICLE)
        return DismissControlledVehicle;
    if (opcode == CMSG_FORCE_MOVE_ROOT_ACK)
        return ForceMoveRootAck;
    if (opcode == CMSG_FORCE_MOVE_UNROOT_ACK)
        return ForceMoveUnrootAck;
    if (opcode == CMSG_MOVE_FALL_RESET)
        return MovementFallReset;
    if (opcode == CMSG_MOVE_FEATHER_FALL_ACK)
        return MovementFeatherFallAck;
    if (opcode == CMSG_MOVE_FORCE_FLIGHT_SPEED_CHANGE_ACK)
        return MovementForceFlightSpeedChangeAck;
    if (opcode == CMSG_MOVE_FORCE_RUN_BACK_SPEED_CHANGE_ACK)
        return MovementForceRunBackSpeedChangeAck;
    if (opcode == CMSG_MOVE_FORCE_RUN_SPEED_CHANGE_ACK)
        return MovementForceRunSpeedChangeAck;
    if (opcode == CMSG_MOVE_FORCE_SWIM_SPEED_CHANGE_ACK)
        return MovementForceSwimSpeedChangeAck;
    if (opcode == CMSG_MOVE_FORCE_SWIM_BACK_SPEED_CHANGE_ACK)
        return MoveForceSwimBackSpeedChangeAck;
    if (opcode == CMSG_MOVE_FORCE_FLIGHT_BACK_SPEED_CHANGE_ACK)
        return MoveForceFlightBackSpeedChangeAck;
    if (opcode == CMSG_MOVE_FORCE_WALK_SPEED_CHANGE_ACK)
        return MovementForceWalkSpeedChangeAck;
    if (opcode == CMSG_MOVE_GRAVITY_DISABLE_ACK)
        return MovementGravityDisableAck;
    if (opcode == CMSG_MOVE_GRAVITY_ENABLE_ACK)
        return MovementGravityEnableAck;
    if (opcode == CMSG_MOVE_HOVER_ACK)
        return MovementHoverAck;
    if (opcode == CMSG_MOVE_KNOCK_BACK_ACK)
        return MovementKnockBackAck;
    if (opcode == CMSG_MOVE_SET_CAN_FLY)
        return MovementSetCanFly;
    if (opcode == CMSG_MOVE_SET_CAN_FLY_ACK)
        return MovementSetCanFlyAck;
    if (opcode == CMSG_MOVE_SET_CAN_TRANSITION_BETWEEN_SWIM_AND_FLY_ACK)
        return MovementSetCanTransitionBetweenSwimAndFlyAck;
    if (opcode == CMSG_MOVE_SET_COLLISION_HEIGHT_ACK)
        return MovementSetCollisionHeightAck;
    if (opcode == SMSG_MOVE_SET_COLLISION_HEIGHT)
        return MovementSetCollisionHeight;
    if (opcode == SMSG_MOVE_UPDATE_COLLISION_HEIGHT)
        return MovementUpdateCollisionHeight;
    if (opcode == CMSG_MOVE_WATER_WALK_ACK)
        return MovementWaterWalkAck;
    if (opcode == MSG_MOVE_SET_RUN_MODE)
        return MovementSetRunMode;
    if (opcode == MSG_MOVE_SET_WALK_MODE)
        return MovementSetWalkMode;
    if (opcode == SMSG_MOVE_UPDATE)
        return MovementUpdate;
    if (opcode == SMSG_MOVE_UPDATE_FLIGHT_SPEED)
        return MovementUpdateFlightSpeed;
    if (opcode == SMSG_MOVE_UPDATE_RUN_SPEED)
        return MovementUpdateRunSpeed;
    if (opcode == SMSG_MOVE_UPDATE_KNOCK_BACK)
        return MovementUpdateKnockBack;
    if (opcode == SMSG_MOVE_UPDATE_RUN_BACK_SPEED)
        return MovementUpdateRunBackSpeed;
    if (opcode == SMSG_MOVE_UPDATE_SWIM_SPEED)
        return MovementUpdateSwimSpeed;
    if (opcode == SMSG_MOVE_UPDATE_SWIM_BACK_SPEED)
        return MoveUpdateSwimBackSpeed;
    if (opcode == SMSG_MOVE_UPDATE_WALK_SPEED)
        return MovementUpdateWalkSpeed;
    if (opcode == SMSG_SPLINE_MOVE_SET_WALK_SPEED)
        return SplineMoveSetWalkSpeed;
    if (opcode == SMSG_SPLINE_MOVE_SET_RUN_SPEED)
        return SplineMoveSetRunSpeed;
    if (opcode == SMSG_SPLINE_MOVE_SET_RUN_BACK_SPEED)
        return SplineMoveSetRunBackSpeed;
    if (opcode == SMSG_SPLINE_MOVE_SET_SWIM_SPEED)
        return SplineMoveSetSwimSpeed;
    if (opcode == SMSG_SPLINE_MOVE_SET_SWIM_BACK_SPEED)
        return SplineMoveSetSwimBackSpeed;
    if (opcode == SMSG_SPLINE_MOVE_SET_TURN_RATE)
        return SplineMoveSetTurnRate;
    if (opcode == SMSG_SPLINE_MOVE_SET_FLIGHT_SPEED)
        return SplineMoveSetFlightSpeed;
    if (opcode == SMSG_SPLINE_MOVE_SET_FLIGHT_BACK_SPEED)
        return SplineMoveSetFlightBackSpeed;
    if (opcode == SMSG_SPLINE_MOVE_SET_PITCH_RATE)
        return SplineMoveSetPitchRate;
    if (opcode == SMSG_MOVE_SET_WALK_SPEED)
        return MoveSetWalkSpeed;
    if (opcode == SMSG_MOVE_SET_RUN_SPEED)
        return MoveSetRunSpeed;
    if (opcode == SMSG_MOVE_SET_RUN_BACK_SPEED)
        return MoveSetRunBackSpeed;
    if (opcode == SMSG_MOVE_SET_SWIM_SPEED)
        return MoveSetSwimSpeed;
    if (opcode == SMSG_MOVE_SET_SWIM_BACK_SPEED)
        return MoveSetSwimBackSpeed;
    if (opcode == SMSG_MOVE_SET_TURN_RATE)
        return MoveSetTurnRate;
    if (opcode == SMSG_MOVE_SET_FLIGHT_SPEED)
        return MoveSetFlightSpeed;
    if (opcode == SMSG_MOVE_SET_FLIGHT_BACK_SPEED)
        return MoveSetFlightBackSpeed;
    if (opcode == SMSG_MOVE_SET_PITCH_RATE)
        return MoveSetPitchRate;
    if (opcode == SMSG_SPLINE_MOVE_SET_WALK_MODE)
        return SplineMoveSetWalkMode;
    if (opcode == SMSG_SPLINE_MOVE_SET_RUN_MODE)
        return SplineMoveSetRunMode;
    if (opcode == SMSG_SPLINE_MOVE_GRAVITY_DISABLE)
        return SplineMoveGravityDisable;
    if (opcode == SMSG_SPLINE_MOVE_GRAVITY_ENABLE)
        return SplineMoveGravityEnable;
    if (opcode == SMSG_SPLINE_MOVE_SET_HOVER)
        return SplineMoveSetHover;
    if (opcode == SMSG_SPLINE_MOVE_UNSET_HOVER)
        return SplineMoveUnsetHover;
    if (opcode == SMSG_SPLINE_MOVE_START_SWIM)
        return SplineMoveStartSwim;
    if (opcode == SMSG_SPLINE_MOVE_STOP_SWIM)
        return SplineMoveStopSwim;
    if (opcode == SMSG_SPLINE_MOVE_SET_FLYING)
        return SplineMoveSetFlying;
    if (opcode == SMSG_SPLINE_MOVE_UNSET_FLYING)
        return SplineMoveUnsetFlying;
    if (opcode == SMSG_SPLINE_MOVE_SET_WATER_WALK)
        return SplineMoveSetWaterWalk;
    if (opcode == SMSG_SPLINE_MOVE_SET_LAND_WALK)
        return SplineMoveSetLandWalk;
    if (opcode == SMSG_SPLINE_MOVE_SET_FEATHER_FALL)
        return SplineMoveSetFeatherFall;
    if (opcode == SMSG_SPLINE_MOVE_SET_NORMAL_FALL)
        return SplineMoveSetNormalFall;
    if (opcode == SMSG_SPLINE_MOVE_ROOT)
        return SplineMoveRoot;
    if (opcode == SMSG_SPLINE_MOVE_UNROOT)
        return SplineMoveUnroot;
    if (opcode == SMSG_MOVE_SET_CAN_FLY)
        return MoveSetCanFly;
    if (opcode == SMSG_MOVE_UNSET_CAN_FLY)
        return MoveUnsetCanFly;
    if (opcode == SMSG_MOVE_SET_HOVER)
        return MoveSetHover;
    if (opcode == SMSG_MOVE_UNSET_HOVER)
        return MoveUnsetHover;
    if (opcode == SMSG_MOVE_WATER_WALK)
        return MoveWaterWalk;
    if (opcode == SMSG_MOVE_LAND_WALK)
        return MoveLandWalk;
    if (opcode == SMSG_MOVE_FEATHER_FALL)
        return MoveFeatherFall;
    if (opcode == SMSG_MOVE_NORMAL_FALL)
        return MoveNormalFall;
    if (opcode == SMSG_MOVE_ROOT)
        return MoveRoot;
    if (opcode == SMSG_MOVE_UNROOT)
        return MoveUnroot;
    if (opcode == CMSG_CHANGE_SEATS_ON_CONTROLLED_VEHICLE)
        return ChangeSeatsOnControlledVehicle;
    if (opcode == CMSG_CAST_SPELL || opcode == CMSG_PET_CAST_SPELL || opcode == CMSG_USE_ITEM)
        return CastSpellEmbeddedMovement;
    if (opcode == SMSG_MOVE_GRAVITY_DISABLE)
        return MoveGravityDisable;
    if (opcode == SMSG_MOVE_GRAVITY_ENABLE)
        return MoveGravityEnable;
    if (opcode == SMSG_MOVE_UPDATE_FLIGHT_BACK_SPEED)
        return MoveUpdateFlightBackSpeed;
    if (opcode == SMSG_MOVE_SET_CAN_TRANSITION_BETWEEN_SWIM_AND_FLY)
        return MoveSetCanTransitionBetweenSwimAndFly;
    if (opcode == SMSG_MOVE_UNSET_CAN_TRANSITION_BETWEEN_SWIM_AND_FLY)
        return MoveUnsetCanTransitionBetweenSwimAndFly;

    return nullptr;
}

void Cataclysm::ReadMovementInfo(WorldPacket& data, MovementInfo& mi, ObjectGuid* guid, uint32* movementCounter, ExtraMovementStatusElement* extras)
{
    MovementStatusElements const* sequence = GetMovementStatusElementsSequence(data.GetOpcode());
    if (!sequence)
    {
        printf("[ERROR] Cataclysm::ReadMovementInfo: No movement sequence found for opcode %s", Opcodes::GetOpcodeName(data.GetOpcode(), sWorld.GetClientBuild()).c_str());
        return;
    }

    bool hasMovementFlags = false;
    bool hasMovementFlags2 = false;
    bool hasTimestamp = false;
    bool hasOrientation = false;
    bool hasTransportData = false;
    bool hasTransportTime2 = false;
    bool hasTransportVehicleId = false;
    bool hasPitch = false;
    bool hasFallData = false;
    bool hasFallDirection = false;
    bool hasSplineElevation = false;

    ObjectGuid tguid;

    for (; *sequence != MSEEnd; ++sequence)
    {
        MovementStatusElements const& element = *sequence;

        switch (element)
        {
            case MSEHasGuidByte0:
            case MSEHasGuidByte1:
            case MSEHasGuidByte2:
            case MSEHasGuidByte3:
            case MSEHasGuidByte4:
            case MSEHasGuidByte5:
            case MSEHasGuidByte6:
            case MSEHasGuidByte7:
                guid[element - MSEHasGuidByte0] = data.ReadBit();
                break;
            case MSEHasTransportGuidByte0:
            case MSEHasTransportGuidByte1:
            case MSEHasTransportGuidByte2:
            case MSEHasTransportGuidByte3:
            case MSEHasTransportGuidByte4:
            case MSEHasTransportGuidByte5:
            case MSEHasTransportGuidByte6:
            case MSEHasTransportGuidByte7:
                if (hasTransportData)
                    tguid[element - MSEHasTransportGuidByte0] = data.ReadBit();
                break;
            case MSEGuidByte0:
            case MSEGuidByte1:
            case MSEGuidByte2:
            case MSEGuidByte3:
            case MSEGuidByte4:
            case MSEGuidByte5:
            case MSEGuidByte6:
            case MSEGuidByte7:
                data.ReadByteSeq((*guid)[element - MSEGuidByte0]);
                break;
            case MSETransportGuidByte0:
            case MSETransportGuidByte1:
            case MSETransportGuidByte2:
            case MSETransportGuidByte3:
            case MSETransportGuidByte4:
            case MSETransportGuidByte5:
            case MSETransportGuidByte6:
            case MSETransportGuidByte7:
                if (hasTransportData)
                    data.ReadByteSeq(tguid[element - MSETransportGuidByte0]);
                break;
            case MSEHasMovementFlags:
                hasMovementFlags = !data.ReadBit();
                break;
            case MSEHasMovementFlags2:
                hasMovementFlags2 = !data.ReadBit();
                break;
            case MSEHasTimestamp:
                hasTimestamp = !data.ReadBit();
                break;
            case MSEHasOrientation:
                hasOrientation = !data.ReadBit();
                break;
            case MSEHasTransportData:
                hasTransportData = data.ReadBit();
                break;
            case MSEHasTransportTime2:
                if (hasTransportData)
                    hasTransportTime2 = data.ReadBit();
                break;
            case MSEHasVehicleId:
                if (hasTransportData)
                    hasTransportVehicleId = data.ReadBit();
                break;
            case MSEHasPitch:
                hasPitch = !data.ReadBit();
                break;
            case MSEHasFallData:
                hasFallData = data.ReadBit();
                break;
            case MSEHasFallDirection:
                if (hasFallData)
                    hasFallDirection = data.ReadBit();
                break;
            case MSEHasSplineElevation:
                hasSplineElevation = !data.ReadBit();
                break;
            case MSEHasSpline:
                data.ReadBit();
                break;
            case MSEHasHeightChangeFailed:
                data.ReadBit();
                break;
            case MSEMovementFlags:
                if (hasMovementFlags)
                    mi.moveFlags = data.ReadBits(30);
                break;
            case MSEMovementFlags2:
                if (hasMovementFlags2)
                    mi.moveFlags2WotLK = data.ReadBits(12);
                break;
            case MSETimestamp:
                if (hasTimestamp)
                    data >> mi.time;
                break;
            case MSEPositionX:
                data >> mi.pos.x;
                break;
            case MSEPositionY:
                data >> mi.pos.y;
                break;
            case MSEPositionZ:
                data >> mi.pos.z;
                break;
            case MSEOrientation:
                if (hasOrientation)
                    mi.pos.o = data.read<float>();
                break;
            case MSETransportPositionX:
                if (hasTransportData)
                    data >> mi.t_pos.x;
                break;
            case MSETransportPositionY:
                if (hasTransportData)
                    data >> mi.t_pos.y;
                break;
            case MSETransportPositionZ:
                if (hasTransportData)
                    data >> mi.t_pos.z;
                break;
            case MSETransportOrientation:
                if (hasTransportData)
                    mi.t_pos.o = data.read<float>();
                break;
            case MSETransportSeat:
                if (hasTransportData)
                    data >> mi.t_seat;
                break;
            case MSETransportTime:
                if (hasTransportData)
                    data >> mi.t_time;
                break;
            case MSETransportTime2:
                if (hasTransportData && hasTransportTime2)
                    data >> mi.t_time2;
                break;
            case MSETransportVehicleId:
                if (hasTransportData && hasTransportVehicleId)
                    data >> mi.t_vehicle;
                break;
            case MSEPitch:
                if (hasPitch)
                    data >> mi.s_pitch;
                break;
            case MSEFallTime:
                if (hasFallData)
                    data >> mi.fallTime;
                break;
            case MSEFallVerticalSpeed:
                if (hasFallData)
                    data >> mi.jump.zspeed;
                break;
            case MSEFallCosAngle:
                if (hasFallData && hasFallDirection)
                    data >> mi.jump.cosAngle;
                break;
            case MSEFallSinAngle:
                if (hasFallData && hasFallDirection)
                    data >> mi.jump.sinAngle;
                break;
            case MSEFallHorizontalSpeed:
                if (hasFallData && hasFallDirection)
                    data >> mi.jump.xyspeed;
                break;
            case MSESplineElevation:
                if (hasSplineElevation)
                    data >> mi.splineElevation;
                break;
            case MSECounter:
                data >> *movementCounter;
                break;
            case MSEZeroBit:
            case MSEOneBit:
                data.ReadBit();
                break;
            case MSEExtraElement:
                extras->ReadNextElement(data);
                break;
            default:
                printf("[ERROR] Cataclysm::ReadMovementInfo Incorrect sequence element %u detected", element);
                break;
        }
    }

    mi.t_guid = tguid;
}

void Cataclysm::WriteMovementInfo(WorldPacket& data, MovementInfo& mi, ObjectGuid* guid, uint32* movementCounter, ExtraMovementStatusElement* extras)
{
    bool hasMovementFlags = mi.moveFlags != 0;
    bool hasMovementFlags2 = mi.moveFlags2WotLK != 0;
    bool hasTimestamp = true;
    bool hasOrientation = mi.pos.o != 0;
    bool hasTransportData = !mi.t_guid.IsEmpty();
    bool hasSpline = mi.moveFlags & WotLK::MOVEFLAG_SPLINE_ENABLED;

    bool hasTransportTime2 = hasTransportData && mi.t_time2 != 0;
    bool hasTransportVehicleId = hasTransportData && mi.t_vehicle != 0;
    bool hasPitch = mi.HasMovementFlag(WotLK::MOVEFLAG_SWIMMING | WotLK::MOVEFLAG_FLYING) || mi.HasMovementFlag2(WotLK::MOVEFLAG2_ALLOW_PITCHING);
    bool hasFallDirection = mi.HasMovementFlag(WotLK::MOVEFLAG_FALLING);
    bool hasFallData = hasFallDirection || mi.fallTime != 0;
    bool hasSplineElevation = mi.HasMovementFlag(WotLK::MOVEFLAG_SPLINE_ELEVATION);

    MovementStatusElements const* sequence = GetMovementStatusElementsSequence(data.GetOpcode());
    if (!sequence)
    {
        printf("[ERROR] Cataclysm::WriteMovementInfo: No movement sequence found for opcode %s", Opcodes::GetOpcodeName(data.GetOpcode(), sWorld.GetClientBuild()).c_str());
        return;
    }

    ObjectGuid tguid = mi.t_guid;

    for (; *sequence != MSEEnd; ++sequence)
    {
        MovementStatusElements const& element = *sequence;

        switch (element)
        {
        case MSEHasGuidByte0:
        case MSEHasGuidByte1:
        case MSEHasGuidByte2:
        case MSEHasGuidByte3:
        case MSEHasGuidByte4:
        case MSEHasGuidByte5:
        case MSEHasGuidByte6:
        case MSEHasGuidByte7:
            data.WriteBit(guid[element - MSEHasGuidByte0]);
            break;
        case MSEHasTransportGuidByte0:
        case MSEHasTransportGuidByte1:
        case MSEHasTransportGuidByte2:
        case MSEHasTransportGuidByte3:
        case MSEHasTransportGuidByte4:
        case MSEHasTransportGuidByte5:
        case MSEHasTransportGuidByte6:
        case MSEHasTransportGuidByte7:
            if (hasTransportData)
                data.WriteBit(tguid[element - MSEHasTransportGuidByte0]);
            break;
        case MSEGuidByte0:
        case MSEGuidByte1:
        case MSEGuidByte2:
        case MSEGuidByte3:
        case MSEGuidByte4:
        case MSEGuidByte5:
        case MSEGuidByte6:
        case MSEGuidByte7:
            data.WriteByteSeq(guid[element - MSEGuidByte0]);
            break;
        case MSETransportGuidByte0:
        case MSETransportGuidByte1:
        case MSETransportGuidByte2:
        case MSETransportGuidByte3:
        case MSETransportGuidByte4:
        case MSETransportGuidByte5:
        case MSETransportGuidByte6:
        case MSETransportGuidByte7:
            if (hasTransportData)
                data.WriteByteSeq(tguid[element - MSETransportGuidByte0]);
            break;
        case MSEHasMovementFlags:
            data.WriteBit(!hasMovementFlags);
            break;
        case MSEHasMovementFlags2:
            data.WriteBit(!hasMovementFlags2);
            break;
        case MSEHasTimestamp:
            data.WriteBit(!hasTimestamp);
            break;
        case MSEHasOrientation:
            data.WriteBit(!hasOrientation);
            break;
        case MSEHasTransportData:
            data.WriteBit(hasTransportData);
            break;
        case MSEHasTransportTime2:
            if (hasTransportData)
                data.WriteBit(hasTransportTime2);
            break;
        case MSEHasVehicleId:
            if (hasTransportData)
                data.WriteBit(hasTransportVehicleId);
            break;
        case MSEHasPitch:
            data.WriteBit(!hasPitch);
            break;
        case MSEHasFallData:
            data.WriteBit(hasFallData);
            break;
        case MSEHasFallDirection:
            if (hasFallData)
                data.WriteBit(hasFallDirection);
            break;
        case MSEHasSplineElevation:
            data.WriteBit(!hasSplineElevation);
            break;
        case MSEHasSpline:
            data.WriteBit(hasSpline);
            break;
        case MSEHasHeightChangeFailed:
            data.WriteBit(0);
            break;
        case MSEMovementFlags:
            if (hasMovementFlags)
                data.WriteBits(mi.moveFlags, 30);
            break;
        case MSEMovementFlags2:
            if (hasMovementFlags2)
                data.WriteBits(mi.moveFlags2WotLK, 12);
            break;
        case MSETimestamp:
            if (hasTimestamp)
                data << mi.time;
            break;
        case MSEPositionX:
            data << mi.pos.x;
            break;
        case MSEPositionY:
            data << mi.pos.y;
            break;
        case MSEPositionZ:
            data << mi.pos.z;
            break;
        case MSEOrientation:
            if (hasOrientation)
                data << mi.pos.o;
            break;
        case MSETransportPositionX:
            if (hasTransportData)
                data << mi.t_pos.x;
            break;
        case MSETransportPositionY:
            if (hasTransportData)
                data << mi.t_pos.y;
            break;
        case MSETransportPositionZ:
            if (hasTransportData)
                data << mi.t_pos.z;
            break;
        case MSETransportOrientation:
            if (hasTransportData)
                data << mi.t_pos.o;
            break;
        case MSETransportSeat:
            if (hasTransportData)
                data << mi.t_seat;
            break;
        case MSETransportTime:
            if (hasTransportData)
                data << mi.t_time;
            break;
        case MSETransportTime2:
            if (hasTransportData && hasTransportTime2)
                data << mi.t_time2;
            break;
        case MSETransportVehicleId:
            if (hasTransportData && hasTransportVehicleId)
                data << mi.t_vehicle;
            break;
        case MSEPitch:
            if (hasPitch)
                data << mi.s_pitch;
            break;
        case MSEFallTime:
            if (hasFallData)
                data << mi.fallTime;
            break;
        case MSEFallVerticalSpeed:
            if (hasFallData)
                data << mi.jump.zspeed;
            break;
        case MSEFallCosAngle:
            if (hasFallData && hasFallDirection)
                data << mi.jump.cosAngle;
            break;
        case MSEFallSinAngle:
            if (hasFallData && hasFallDirection)
                data << mi.jump.sinAngle;
            break;
        case MSEFallHorizontalSpeed:
            if (hasFallData && hasFallDirection)
                data << mi.jump.xyspeed;
            break;
        case MSESplineElevation:
            if (hasSplineElevation)
                data << mi.splineElevation;
            break;
        case MSECounter:
            data << uint32(movementCounter ? *movementCounter : 0);
            break;
        case MSEZeroBit:
            data.WriteBit(0);
            break;
        case MSEOneBit:
            data.WriteBit(1);
            break;
        case MSEFlushBits:
            data.FlushBits();
            break;
        case MSEExtraElement:
            extras->WriteNextElement(data);
            break;
        default:
            printf("[ERROR] Cataclysm::WriteMovementInfo Incorrect sequence element %u detected", element);
            break;
        }
    }
}
