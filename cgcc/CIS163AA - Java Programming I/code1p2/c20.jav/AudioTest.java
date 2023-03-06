import java.awt.*; 
import java.applet.*;
import java.awt.event.*;

public class AudioTest extends Applet
    implements ActionListener {
    Button play, loop, stop;
    AudioClip sound;

    public void init() {
        play = new Button("Play");
        add(play);
        play.addActionListener(this);
        loop = new Button("Loop");
        add(loop);
        loop.addActionListener(this);
        stop = new Button("Stop");
        add(stop);
        stop.addActionListener(this);
        sound = getAudioClip(getDocumentBase(), "sound.au");
    }

    public void actionPerformed(ActionEvent event) {
        if (event.getSource() == play) play();
        if (event.getSource() == loop) loop();
        if (event.getSource() == stop) stop();
    }

    public void stop() {
        sound.stop();
    }

    public void play() {
        sound.play();
    }

    public void loop() {
        sound.loop();
    }
}

