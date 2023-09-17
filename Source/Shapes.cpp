/*
  ==============================================================================

    Shapes.cpp
    Created: 7 Apr 2023 7:25:12pm
    Author:  G

  ==============================================================================
*/

#include "Shapes.h"



/// <summary>
/// Draws the path for the "eject" symbol
///
///     /\
///    /  \
///   /    \
///  /______\
///  ________
/// |________|
///
/// </summary>
/// <returns>Path openButtonPath - A path for the "Eject" symbol</returns>
Path Shapes::getOpenButtonPath()
{
    Path openButtonPath;

    //Draw the triangle
    openButtonPath.startNewSubPath
    (
        20,
        10
    );
    openButtonPath.lineTo
    (
        10,
        20
    );
    openButtonPath.lineTo
    (
        30,
        20
    );
    openButtonPath.closeSubPath();

    //Draw the line
    openButtonPath.startNewSubPath
    (
        10,
        25
    );
    openButtonPath.lineTo
    (
        10,
        30
    );
    openButtonPath.lineTo
    (
        30,
        30
    );
    openButtonPath.lineTo
    (
        30,
        25
    );
    openButtonPath.closeSubPath();

    return openButtonPath;
}

/// <summary>
/// Draws the path for the "Skip to start" symbol and returns it
///
/// |   /|
/// |  / |
/// |  \ |
/// |   \|
///
/// </summary>
/// <returns>Path skipToStartButtonPath - A path for the "Skip to start" symbol</returns>
Path Shapes::getSkipToStartButtonPath()
{
    Path skipToStartButtonPath;       //Create a Path

    skipToStartButtonPath.startNewSubPath   //Start drawing at 10, 10
    (
        10,                                 //Start at X
        10                                  //Start at Y
    );

    skipToStartButtonPath.lineTo            //Draw a line to a10, 40 (The vertical line
    (
        10,                                 //Draw to X
        40                                  //Draw to Y
    );

    skipToStartButtonPath.lineTo
    (
        15,
        40
    );

    skipToStartButtonPath.lineTo
    (
        15,
        10
    );

    skipToStartButtonPath.closeSubPath();   //Stop drawing (closeSubPath)

    skipToStartButtonPath.startNewSubPath   //Create a new subPath
    (
        40,                                 //Start at X
        10                                  //Start at Y
    );

    skipToStartButtonPath.lineTo            //Draw line to 20, 20
    (
        20,                                 //Draw to X
        25                                  //Draw to Y
    );

    skipToStartButtonPath.lineTo
    (
        40,
        40
    );

    skipToStartButtonPath.closeSubPath();


    return skipToStartButtonPath;
}

/// <summary>
/// Draws the path for the "Rewind" symbol and returns it
///
///  /|  /|
/// / | / |
/// \ | \ |
///  \|  \|
/// 
/// </summary>
/// <returns>Path skipToStartButtonPath - A path for the "Rewind" symbol</returns>
Path Shapes::getRewindButtonPath()
{
    Path rewindButtonPath;
    //First triangle
    rewindButtonPath.startNewSubPath
    (
        30,
        10
    );

    rewindButtonPath.lineTo
    (
        10,
        25
    );

    rewindButtonPath.lineTo
    (
        30,
        40
    );

    rewindButtonPath.closeSubPath();

    //Second triangle
    rewindButtonPath.startNewSubPath
    (
        50,
        10
    );

    rewindButtonPath.lineTo
    (
        30,
        25
    );

    rewindButtonPath.lineTo
    (
        50,
        40
    );

    rewindButtonPath.closeSubPath();


    return rewindButtonPath;
};

/// <summary>
/// Makes the path of a rectangle (Stop symbol) and returns it
///  ________
/// |        |
/// |        |
/// |        |
/// |________|
/// 
/// </summary>
/// <returns>Path </returns>
Path Shapes::getStopButtonPath()
{
    //Make the stop button path (a square)
    Path stopButtonPath;
    stopButtonPath.addRectangle
    (
        10,     //Start X
        10,     //Start Y
        30,     //Width
        30      //Height
    );

    return stopButtonPath;
}

/// <summary>
/// Draws the path for the "Play" symbol and returns it\
/// 
/// 
///  |\
///  | \
///  | /
///  |/
/// 
/// </summary>
/// <returns></returns>
Path Shapes::getPlayButtonPath()
{
    Path playButtonPath;

    playButtonPath.startNewSubPath
    (
        10,
        10
    );

    playButtonPath.lineTo
    (
        10,
        40
    );

    playButtonPath.lineTo
    (
        40,
        25
    );

    playButtonPath.closeSubPath();


    return playButtonPath;
}

/// <summary>
/// Draws the path for the "Pause" symbol and returns it
///   __   __
///  |  | |  |
///  |  | |  |
///  |  | |  |
///  |__| |__|
///
/// </summary>
/// <returns></returns>
Path Shapes::getPauseButtonPath()
{
    Path pauseButtonPath;

    pauseButtonPath.startNewSubPath
    (
        10,
        10
    );
    pauseButtonPath.lineTo
    (
        10,
        40
    );
    pauseButtonPath.lineTo
    (
        20,
        40
    );
    pauseButtonPath.lineTo
    (
        20,
        10
    );
    pauseButtonPath.closeSubPath();

    pauseButtonPath.startNewSubPath
    (
        30,
        10
    );
    pauseButtonPath.lineTo
    (
        30,
        40
    );
    pauseButtonPath.lineTo
    (
        40,
        40
    );
    pauseButtonPath.lineTo
    (
        40,
        10
    );
    pauseButtonPath.closeSubPath();


    return pauseButtonPath;
}

/// <summary>
/// Draws the path for the "Fast sorward" symbol and returns it
///
/// |\  |\
/// | \ | \
/// | / | /
/// |/  |/
/// 
/// </summary>
/// <returns>Path skipToStartButtonPath - A path for the "Rewind" symbol</returns>
Path Shapes::getFastForwardButtonPath()
{
    Path fastForwardButtonPath;

    fastForwardButtonPath.startNewSubPath
    (
        10,
        10
    );
    fastForwardButtonPath.lineTo
    (
        10,
        40
    );
    fastForwardButtonPath.lineTo
    (
        30,
        25
    );
    fastForwardButtonPath.closeSubPath();


    fastForwardButtonPath.startNewSubPath
    (
        30,
        10
    );
    fastForwardButtonPath.lineTo
    (
        30,
        40
    );
    fastForwardButtonPath.lineTo
    (
        50,
        25
    );
    fastForwardButtonPath.closeSubPath();


    return fastForwardButtonPath;
}

/// <summary>
/// Draws the path for the "Skip to end" symbol and returns it
///
/// |\  |
/// | \ |
/// | / |
/// |/  |
///
/// </summary>
/// <returns>Path skipToStartButtonPath - A path for the "Skip to end" symbol</returns>
Path Shapes::getSkipToEndButtonPath()
{
    Path skipToEndButtonPath;

    skipToEndButtonPath.startNewSubPath
    (
        10,
        10
    );
    skipToEndButtonPath.lineTo
    (
        10,
        40
    );
    skipToEndButtonPath.lineTo
    (
        30,
        25
    );
    skipToEndButtonPath.closeSubPath();

    skipToEndButtonPath.startNewSubPath
    (
        40,
        10
    );
    skipToEndButtonPath.lineTo
    (
        40,
        40
    );
    skipToEndButtonPath.lineTo
    (
        45,
        40
    );
    skipToEndButtonPath.lineTo
    (
        45,
        10
    );
    skipToEndButtonPath.closeSubPath();

    return skipToEndButtonPath;
}


/** Shapes */
    /** Returns a sawtooth shaped Path */
Path Shapes::getSawtoothPath(Rectangle<float>&& buttonBounds)
{
    buttonBounds.reduced(6, 6);

    /** Bounds dimensions. */
    float boundsX = buttonBounds.getX();
    float boundsY = buttonBounds.getY();
    float boundsWidth = buttonBounds.getWidth();
    float boundsHeight = buttonBounds.getHeight();

    //float buttonSide

    /** Button X and Y centers */
    float centerX = boundsWidth / 2.f;
    float centerY = boundsHeight / 2.f;

    auto sawtoothPath = Path();

    /** Design the sawtooth path. */
    sawtoothPath.startNewSubPath(centerX - centerY, boundsY + centerY);
    sawtoothPath.lineTo(centerX, boundsY + boundsHeight * 0.2f);
    sawtoothPath.lineTo(centerX, boundsY + boundsHeight * 0.8f);
    sawtoothPath.lineTo(centerX + centerY, boundsY + centerY);

    return sawtoothPath;
}

/** Returns a pulse shaped Path */
Path Shapes::getPulsePath(Rectangle<float>&& buttonBounds)
{
    buttonBounds.reduced(6, 6);

    /** Bounds dimensions. */
    float boundsX = buttonBounds.getX();
    float boundsY = buttonBounds.getY();
    float boundsWidth = buttonBounds.getWidth();
    float boundsHeight = buttonBounds.getHeight();

    //float buttonSide

    /** Button X and Y centers */
    float centerX = boundsWidth / 2.f;
    float centerY = boundsHeight / 2.f;

    auto pulsePath = Path();

    /** Design the pulse path. */
    pulsePath.startNewSubPath(centerX - centerY, boundsY + centerY);
    pulsePath.lineTo(centerX - centerY, boundsY + boundsHeight * 0.2f);	//Up
    pulsePath.lineTo(centerX - centerY / 3.f, boundsY + boundsHeight * 0.2f);	//Right
    pulsePath.lineTo(centerX - centerY / 3.f, boundsY + boundsHeight * 0.8f);	//Down
    pulsePath.lineTo(centerX + centerY, boundsY + boundsHeight * 0.8f);	//Right
    pulsePath.lineTo(centerX + centerY, boundsY + boundsHeight / 2.f);	//Up


    return pulsePath;
}

/** Returns a triangle shaped Path */
Path Shapes::getTrianglePath(Rectangle<float>&& buttonBounds)
{
    buttonBounds.reduced(6, 6);

    /** Bounds dimensions. */
    float boundsX = buttonBounds.getX();
    float boundsY = buttonBounds.getY();
    float boundsWidth = buttonBounds.getWidth();
    float boundsHeight = buttonBounds.getHeight();

    //float buttonSide

    /** Button X and Y centers */
    float centerX = boundsWidth / 2.f;
    float centerY = boundsHeight / 2.f;

    auto trianglePath = Path();

    /** Design the triangle path. */
    trianglePath.startNewSubPath(centerX - centerY, boundsY + centerY);
    trianglePath.lineTo(centerX - centerY / 2.f, boundsY + boundsHeight * 0.2f);	//Up-Rigth
    trianglePath.lineTo(centerX, centerY);	//Center
    trianglePath.lineTo(centerX + centerY / 2.f, boundsY + boundsHeight * 0.8f);	//Down
    trianglePath.lineTo(centerX + centerY, boundsY + centerY);	//Up-Right



    return trianglePath;
}

/** Returns a sinewave shaped Path */
Path Shapes::getSinewavePath(Rectangle<float>&& buttonBounds)
{
    buttonBounds.reduced(6, 6);

    /** Bounds dimensions. */
    float boundsX = buttonBounds.getX();
    float boundsY = buttonBounds.getY();
    float boundsWidth = buttonBounds.getWidth();
    float boundsHeight = buttonBounds.getHeight();

    //float buttonSide

    /** Button X and Y centers */
    float centerX = boundsWidth / 2.f;
    float centerY = boundsHeight / 2.f;

    auto sinewavePath = Path();

    /** Design the sinewave path. */
    sinewavePath.startNewSubPath(centerX - centerY, boundsY + centerY);
    sinewavePath.addArc(
        centerX - centerY,	// X
        boundsY + boundsHeight * 0.2f,	// Y
        boundsHeight / 2.f,
        boundsHeight * 0.6f,
        -0.5f * float_Pi,
        0.5f * float_Pi
    );
    sinewavePath.addArc(
        centerX,
        boundsY + boundsHeight * 0.2f,
        boundsHeight / 2.f,
        boundsHeight * 0.6f,
        -0.5f * float_Pi,
        -1.5f * float_Pi
    );



    return sinewavePath;
}

/** Returns a noise shaped Path */
Path Shapes::getNoisePath(Rectangle<float>&& buttonBounds)
{
    Path noisePath;

    buttonBounds.reduced(6, 6);

    /** Bounds dimensions. */
    float boundsX = buttonBounds.getX();
    float boundsY = buttonBounds.getY();
    float boundsWidth = buttonBounds.getWidth();
    float boundsHeight = buttonBounds.getHeight();

    //float buttonSide

    /** Button X and Y centers */
    float centerX = boundsWidth / 2.f;
    float centerY = boundsHeight / 2.f;
    float stepX = boundsWidth / 9.f;

    /** Instance of Random. */
    Random random;

    /** Design the noise path. */
    noisePath.startNewSubPath(centerX - centerY, boundsY + centerY);
    for (int i = 1; i < 6; i++)
    {
        noisePath.lineTo(centerX - centerY + stepX * i, boundsY + boundsHeight * 0.2f + random.nextFloat() * 0.6f * boundsHeight);
    }
    noisePath.lineTo(centerX + centerY, boundsY + centerY);

    return noisePath;
}

    // Slider and knob shapes
    Path Shapes::getGearShapedPath(int numberOfSides, float totalDiameter, float totalCenterX, float totalCenterY, float knobGearInnerDiameter)
    {
        Path gearShapedKnobPath;
        /** Circle to take an arc from */
        float radiusOfCircleToTakeArcFrom = 0.25f * totalDiameter;
        float circleToTakeArcFrom_CenterX = totalCenterX;
        float circleToTakeArcFrom_CenterY = totalCenterY - knobGearInnerDiameter;
        float circleToTakeArcFrom_Radius = knobGearInnerDiameter / 2.f;
        constexpr float eighthOfCircleRadians = MathConstants<float>::pi / 4.f;
        /** The gear shape will be created by drawing arcs, connecting them
         * (to make the outer flat bits) and then filling the inside. */
        for (int i = 0; i < numberOfSides; i++)
        {
            bool beginNewSubpath = (i == 0) ? true : false;	// New path for the 1st arc only so that the rest are connected.
            gearShapedKnobPath.addCentredArc(
                circleToTakeArcFrom_CenterX,	//centerX
                circleToTakeArcFrom_CenterY,	//centerY
                circleToTakeArcFrom_Radius,	//radiusX
                circleToTakeArcFrom_Radius,	//radiusY
                0,	// Angle by which the whole ellipse should be rotated about its centre, in radians (clockwise)
                3.5f * eighthOfCircleRadians,	// From radians
                4.5f * eighthOfCircleRadians,	// To radians
                beginNewSubpath);
            gearShapedKnobPath.applyTransform(AffineTransform::rotation(eighthOfCircleRadians, totalCenterX, totalCenterY));
        }
        gearShapedKnobPath.closeSubPath();

        return gearShapedKnobPath;
    }
