# skeleton-animation-editor
An editor that uses a quaternion based keyframe system, or plays .amc animations.

This is an exercise, and a work in progress.

It loads .asf skeleton files, then it can play .amc animation files containing joint names that match the skeleton.
The .amc and keyframe animations have different playback methods but new keyframes are copied from the state of the skeleton at any time,
so new keyframe poses may be extracted during .amc playback.

It loads and saves sets of keyframes to text files (I havnt decided on an extension yet).

TODO: implement the export to .amc
