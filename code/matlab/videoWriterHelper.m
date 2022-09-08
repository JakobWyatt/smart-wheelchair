function videoWriterHelper(fn, frames, framerate)
    v = VideoWriter(fn, "MPEG-4");
    v.FrameRate = framerate;
    open(v);
    writeVideo(v, cell2mat(frames));
    close(v);
end
