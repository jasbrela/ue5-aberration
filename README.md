<p align=center>
  <img width="100%" src="https://github.com/jasbrela/ue5-aberration/blob/main/imgs/aberration_express.gif" />
</p>

# Aberration Express
You’ve already signed the papers, so let’s skip the formalities. Your job is simple: monitor the train. Move through each coach, observe everything carefully, and take notes. If something doesn't match, it's an aberration. Once you leave a coach, there's no going back. At the end of each coach, you’ll be filling out a report on what you saw.

***
<center>
  <div>
    <h1 align=center><a href='https://jasbrela.itch.io/aberration-express'>PLAY IT HERE</a></h1>
    <p align=center>Feedback is always welcome!</p>
  </div>
</center>

***

## Acerola Jam
Aberration Express was initially created for the Acerola Jam 0, which lasted 15 days. The game ranked 15th out of 930 submissions 🥳. The jam’s rule was that participants had to complete a game solo (no teams allowed!) and preferably create their own assets. Although using free or open-source assets was allowed, I accepted the challenge of creating everything from scratch. The final result wasn’t perfectly optimized, but I was proud of it, and especially of the process, where I learned a lot besides programming.

## One Year Later...
A year after the release, when I was exploring UI possibilities in Unreal Engine, I realised Aberration Express was the perfect project for me to learn Common UI, MVVM and UI performance and best practices in general. All the feedback I received during the jam pointed out to a UI refactor. Since I had to redesign the terminal's UI anyway, I decided to use this opportunity to experiment with both plugins.

This led to the current version of Aberration Express. I didn't just upgrade the UI, but the game as a whole:
- Improved performance by reviewing the UI widgets and disabling some default Unreal Engine settings
- Learned some basic VFX (something very new to me at the time)
- Added more interesting aberrations
- Fixed a lot of bugs 🐞

<p align=center>
  <img width="100%" src="https://github.com/jasbrela/ue5-aberration/blob/main/imgs/before_after_1.png" />
  <em>Before and after the UI refactor.</em>
</p>

# Highlights
Switching to Common UI was life changing. If I had known this plugin existed back then when I started developing the game, my life would have been much easier. In the first version, I had to implement selectable button functionality and styles from scratch. While it worked, the workflow felt like a hacky workaround.

Separating gameplay from UI with the MVVM plugin also simplified the development. With the systems separated, I could focus on programming the game logic without worrying about updating text values manually at the same time. Once everything was set up, making the UI functional became much easier: I just had to plug in the components and the bindings.
