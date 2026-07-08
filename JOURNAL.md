## 7/28 (+29th bc midnight): begin
not really "beginning" per se given i'd considered it already before but- you get the idea
I spent some time researching the how i would make the project, which was a bit slow given I don't have experience with dev boards and the like,
I looked into what parts i could use, whether that be a raspberry pi (like a zero 2 w or zero wh), an orange pi, a radxa; it was a bit difficult to find boards that might work and were prices okay
the reason for the difficulty being that early on when looking at an esp32 cam, i search for it on amazon and found the [Seeed Studio XIAO ESP32 S3 Sense](https://www.amazon.com/Seeed-Studio-XIAO-ESP32-Sense/dp/B0C69FFVHH), which led to me reading this review:
![](https://cdn.hackclub.com/019f43fe-58e8-7e98-8661-9858877456cb/review_image.png)
I hadn't considered prior that the board might overheat... that would be an issue - which led me to looking at the aforementioned SBCs.

However, there is of course a critical issue with the vast majority of options I found, which was cost, or in the case of the radxa zero 3w, availability and shipping, of which I only found options that were expensive, slow, and vague, making it an non option. I did not want to start by spending a bunch of money on something I knew very little about.
I also pivoted in the middle of researching when I realized i could take a few parts from things I already had, like the possibility of using a webcam or wifi dongle.
In the end, I decided that I would probably go with the Raspberry Pi Zero WH, given its price not being $40-60 and instead being at around $25.

**2 hr**
*does this time count? no idea*

## 7/29 (+30th bc midnight)
I realized I might actually be able to use an old chromebook i had with a broken cable for the internal display, especially bc it saves money and shipping time idk but also bc i keep getting conflicting info about overheating so I'm kinda worried, and also also because it might let me do a bit more locally. This didn't actually work tho...
my plan was to install linux on it so that i could actually run my stuff and id heard it was possible before, so i checked and it could in fact take linux! i took apart the chromebook to disconnect the screen and got it booted up (yay!) but i could not for the life of my get into recovery mode to turn on developer mode. I tried to see if maybe it might only show on the internal screen, so i opened it up yet again in order to position the screen differently, since id remembered that if it was positioned in *just the right way* it would sometimes maybe show an image. while taking it apart, i realized that one of the screws for the hinge was stripped. i then spent far too long trying every way i could to get it out with different tools, cutting it with a dremel, and drilling it out, all of which did not work- but i finally was able to just rip it out and got back to it. as i was repositioning the screen, though, i saw a glimpse of hope as i saw a dim image, so i turned off my desk lamp to look closer and then was never able to turn it on again.
![](https://cdn.hackclub.com/019f4403-59d2-7140-8495-b778ca7e208d/1-1.png)
![](https://cdn.hackclub.com/019f4403-57c5-7e5f-9c61-c0f4cae5e0a4/1-2.png)
![](https://cdn.hackclub.com/019f4403-55d4-78b4-99f5-fa98c296997c/1-3.png)
![](https://cdn.hackclub.com/019f4403-53db-7e5c-bd29-0a0cf6a326a3/1-4.png)
![](https://cdn.hackclub.com/019f4403-5197-7062-80c1-3492abc80758/1-5.png)
![](https://cdn.hackclub.com/019f4403-4fa0-7cad-9551-bba990499e94/1-6.png)
![](https://cdn.hackclub.com/019f4403-4dac-7156-9a48-1059669ad02c/1-7.png)
**5 hr**
*does this time count? i dont think so ...*
## 7/30
i got up to work with the chromebook again and wasted my time, because a few hours in i realized that 2 resistors got knocked off. i tried to see if i could reattach them without microsoldering, but no.

thats ok though, since i realized that i could take apart *another* broken laptop with a broken chassis and missing ssd instead, and then had to deal with one of the hinge screws rotating because the nut keeping it in was rotating freely... but i eventually got it out and it went much more smoothly than the chromebook
![](https://cdn.hackclub.com/019f43fe-69fb-76bb-af72-fb717a084b2d/2-1.jpg)
![](https://cdn.hackclub.com/019f43fe-67d2-7c48-90f3-815ae8d0d715/2-2.jpg)
**4 hr**

## 7/30
research and plan the robot

**idk hours - 0hr**
## 7/1 + 7/2 after midnight
research motors, components, datasheet,

**4hr**

## 7/2 + 7/3 midnght
i look for the the motors and the wheels

**3hr at least wow im so slow**

## 7/3 + 7/4 midn
full BOM (research other parts) + considering CAD
**5hr**

## 7/5 (+ midnight ofc)
Started working on the CAD, first time doing cad other than tinkercad ever
i decided to use freecad, and i struggled with the partdesign and the concept of workbenches generally for a while, but i kinda figured it out eventually although i did a bunch of things so many times
particularly trying to figure out how to do the wheel wells / holes for the wheels took me forever
i got 3d models for the components that i could find models for, which were useful later to design around
i got the basic form down but not being familiar definitely made it slower![](https://cdn.hackclub.com/019f43fe-5ab4-72fa-9df5-63e6ce1bf240/progress.png)
part of the time spent
https://lapse.hackclub.com/timelapse/-FnbLaLJbWd0
**(3+8=11hr)**

## 7/6 (+ midnight ofc)
i thought i was pretty close, so continuing from the chamfer i ended the previous session with, i decided i could continue adding some chamfers and fillets to the model. big mistake, because after doing that i decided i might want to add a second level easy enough, just add a few pegs. but actually, unbeknownst to me, i could no longer work with the model. no matter what i did, as soon as i padded/extruded from my sketch, the model would simply disappear, except when pocket/removing sometimes, which might add material. this was baffling to me, and after spending forever trying to figure it out, i decided it might be because i was trying to pad into a curved surface. thus, i ended up doing the pegs/supports from a separate body. i had to get back to working with the main body though, since i remembered i needed to add a mount for the caster wheel, which would need to have a piece carved out of the back and probably a mount as well. i looked at what little i could find of the dimensions of the caster wheel, which compared to the other components was so very little. i made the sketches, and removed material, but then i realized i should actually have added material first. no issue, except when i got it, i realized id messed something up, as although i was starting from a flat surface this time, it continued to disappear as soon as i added additive loft or pad and randomly decide whether pocket might add some material. being new to the program, i wasn't sure what i'd done wrong, and so looked through whether i should have used a different tool instead (looking back, i don't think so). at this point, i thought id probably messed up something earlier in the process, and decided to change the tip in an attempt to figure out where i went wrong, but was unsuccessful. i also couldn't find encountering remotely the same issue, except in one reddit post, which wasn't quite the issue, but also had no replies
https://www.reddit.com/r/FreeCAD/comments/sri91z/partdesign_pocket_is_adding_material_and_pad_is/?solution=352db02800b915ab352db02800b915ab&js_challenge=1&token=7afd7253fec22262ff1c52b1703fe9ec6141bee1944d09928cffa39ddfb463ce&jsc_orig_r=
incredible
![](https://cdn.hackclub.com/019f43fe-63e4-7c75-a852-89ebcbc494e4/history.png)
![](https://cdn.hackclub.com/019f43fe-61de-7302-8019-ba1fdd72af46/history1.png)
![](https://cdn.hackclub.com/019f43fe-601a-7794-a91d-03495dcdca10/history2.png)
i eventually started considering exporting what i had and working on the model with all my previous work condensed into a single object, but realized that would not work, since the exported object had impossible geometry
![](https://cdn.hackclub.com/019f43fe-65c7-7b09-8e1b-d8b324250cc8/brokengeo.png)
and that i would not be able to properly work with the model
i think i lost it...
**8hr**

## 7/8
i decided that even though i had determined during the previous sessions that the issue was not the chamfers and fillets i added, since check geometry apparently had issues with my third step and my issues weren't solved when i moved tip the time before, i would try doing the same thing again. this time, it seemed to have fixed the issue, which don't know why. (after finishing the model, i went back to check the geometry of the 3rd step of the model, where the error no longer exists ?) but anyway, after fixing the issue i was encountering, i went back to modeling the wheel well for the caster wheel, and eventually finished it, + adding the top![](https://cdn.hackclub.com/019f43fe-5c8b-7554-ba40-8f022bb6c021/progend.png)
add minimal code

smh too late
**5 hr**