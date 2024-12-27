#include "colors.h"

const Color midnightStorm = {50, 50, 60, 255};
const Color forestGlow = {34, 177, 76, 255};
const Color crimsonBlaze = {237, 28, 36, 255};
const Color sunsetBurst = {255, 127, 39, 255};
const Color goldenRay = {255, 242, 0, 255};
const Color violetDream = {163, 73, 164, 255};
const Color oceanBreeze = {0, 183, 195, 255};
const Color azureWave = {0, 102, 204, 255};
const Color skyDusk = {112, 146, 190, 255};
const Color deepNight = {33, 50, 150, 255};
const Color charcoalMist = {20, 20, 20, 255};

std::vector<Color> GetCellColor() {
    return {midnightStorm, forestGlow, crimsonBlaze, sunsetBurst, goldenRay, violetDream, oceanBreeze, azureWave, skyDusk, deepNight, charcoalMist};
}
