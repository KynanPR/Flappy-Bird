Hey Guys super sorry but wont be able to make it to tommorows session (18th) my car broke down but it will be sorted and ill be back in on the 19th again super sorry for not being in person 
i'll continue working on stuff at home made some changes to the working on background branch if you wanna see if it actually works as my computer didn't want to run it

here is a short description of how what i made works 
So the background system is doing two main things:
1) It scrolls the background forever (like Flappy Bird).
Each background image is drawn using two sprites side-by-side. Every frame both sprites move left a little bit. When one sprite goes completely off the screen, it gets moved to the right side of the other sprite. That way the background loops seamlessly and you never see a gap.
2) It fades into a new background when the score hits a certain point.
The class keeps two “layers”:
current = the background you’re currently seeing
next = the one we’re switching to (only used during a transition)
When the score reaches the next threshold (controlled by scoreStep), the code starts a transition:
next is set to the new texture
next is lined up to the same scroll position as current (so it doesn’t jump)
then over transitionDuration seconds:
current fades from fully visible → invisible
next fades from invisible → fully visible
The fade uses a small easing function (smoothstep) so it looks more natural (it eases in/out instead of being a harsh linear fade).
How the textures are loaded
The background images are loaded once at startup:
GameManager::loadAssets() passes in a list of file paths like
assets/Background/Background1.png … Background6.png
Background::init() loads them using LoadTexture() in Utils
The Background class actually stores the textures internally in a vector, so we don’t have to worry about texture pointers going out of scope.
When it switches backgrounds
It changes every scoreStep points.
Example: if scoreStep = 5, it switches at 5, 10, 15, 20, etc.
The next background is chosen by doing:
(score / scoreStep) % numberOfBackgrounds
So if we run out of backgrounds it just loops back to the start.
Test mode vs real scoring
Right now the code increases the score automatically once per second just so we can easily test transitions without the rest of the game finished yet. Later we’ll remove that and only increase the score when the player actually passes a pipe.
