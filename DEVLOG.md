### Dev Log: Game Engine Development Progress (Waypoint 1)

**Date:** December 14, 2024

---

#### **Overview of Progress:**
The development of our simple game engine has progressed with a focus on setting up basic windows using SDL2 and rendering functionality. Here's a summary of the work completed so far:

1. **Initial Setup**: 
   - Installed and initialized SDL2 and SDL2_ttf libraries, allowing for window creation and text rendering.
   - Configured the game to display two separate windows: one for the GUI (showing an FPS counter) and another for rendering (displaying a static blue background).

2. **Window Creation**: 
   - Implemented functionality to create two SDL2 windows:
     - The first window is dedicated to the GUI and will show debug information (e.g., FPS counter).
     - The second window is reserved for the rendering of game visuals (e.g., 3D models, textures).
   - Both windows are rendered using SDL2's hardware-accelerated renderers.

3. **FPS Counter**:
   - Introduced a basic FPS counter, calculated each frame by measuring time between ticks using SDL_GetTicks.
   - Displayed the FPS value in the GUI window using SDL2_ttf's text rendering functionality.

4. **Rendering Pipeline**:
   - Set up the basic structure for the rendering pipeline. Currently, the second window displays a simple blue background as a placeholder for the game’s future rendering logic.

---

#### **Problems Encountered:**

1. **Segmentation Faults**:
   - Initially, when running the program, we encountered segmentation faults. After careful debugging, it was determined that the issue was with how resources like the font file were being accessed.
   - The program crashed due to trying to load the font from an incorrect or non-existent path, which was resolved by ensuring that the correct font path was used (`/usr/share/fonts/TTF/DejaVuSans-Bold.ttf`).
   - Once the correct paths were provided and the resources loaded successfully, the program started behaving as expected.

2. **Missing SDL2_ttf Library**:
   - At first, we were missing the SDL2_ttf library, which caused the program to fail when attempting to render text.
   - This was resolved by installing the necessary package (`sdl2_ttf`), which allowed the program to proceed to the font rendering stage.

3. **`stdbool.h` Inclusion**:
   - The program failed to compile initially due to the use of `bool`, `true`, and `false` without including the proper header file (`<stdbool.h>`).
   - This was easily fixed by adding `#include <stdbool.h>` to the top of the source file. It’s a common issue when working with Boolean values in C and was a simple oversight.

4. **SDL2 Initialization Issues**:
   - Another early challenge was ensuring that SDL2 was properly initialized. Missing or incorrect calls to `SDL_Init` or `TTF_Init` caused failures in initializing the SDL subsystems.
   - This was tracked down by adding error messages that displayed the SDL-specific error (`SDL_GetError`) and TTF-specific error (`TTF_GetError`), which helped pinpoint the root cause.

---

#### **Next Steps:**

Now that we have the basic functionality working (two windows, FPS counter, and blue background rendering), the next steps include:

1. **Game Rendering**: 
   - Begin integrating actual game rendering, such as drawing shapes, textures, or more complex graphics in the second window (render window).
   
2. **More Advanced Features**:
   - Implement more features for the GUI window, such as buttons, sliders, or other debug information (e.g., memory usage, performance profiling).
   
3. **Game Logic**:
   - Start building out the game loop with more logic, like handling user input (keyboard, mouse), physics, and gameplay mechanics.

4. **Optimizations and Refactoring**:
   - As the engine grows, we will need to optimize the resource management and refactor the code for scalability (e.g., object-oriented design or component-based systems).

---

#### **Conclusion:**

So far, the project is moving smoothly, and we’ve managed to get the basic foundation for the game engine up and running. By creating separate windows for the GUI and game rendering, we have set the stage for more complex features to be added later. The FPS counter serves as a solid first step in monitoring performance, and resolving the issues with SDL2 and font loading has prepared us for upcoming development. Moving forward, the focus will be on enhancing rendering capabilities and integrating more game-related logic into the engine.

---

That’s the current state of the game engine development! It's been an exciting journey so far, and there's much more to come.
