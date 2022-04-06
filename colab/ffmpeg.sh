#!/bin/bash
ffmpeg -f concat -safe 0 -i list.txt -c copy <output>.mp4
ffmpeg -i <input>.MP4 -map 0:v -c copy <output>.mp4
