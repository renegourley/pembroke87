#include <stdint.h>
typedef uint32_t uint;
#include "Board.h"
#include "OutflowPipe.h"

#include "gtest/gtest.h"

class TestBoard: public Board {
public:
    uint _volume;
    uint _playing;
    int _volumeCalls = 0;
    int _playCalls = 0;
    int _stopCalls = 0;
    TestBoard() {
        _volume = 1;
        _playing = 1;
        _volumeCalls = 0;
    }
    void mp3Play(uint track) override {
        _playing = track;
        _playCalls += 1;
    }
    void mp3Stop() override {
        _playing = 0;
        _stopCalls += 1;
    }
    void mp3Volume(uint level) override {
        _volume = level;
        _volumeCalls += 1;
    }
    unsigned long millisecondsSinceBoot() {
        return 3;
    }
    bool isPlaying() {
        return _playing != 0;
    }
    bool getVolume() {
        return _volume;
    }
};

TEST(OutflowPipeTests, Initialize_ShouldBeSilent) {
    TestBoard board;
    OutflowPipe pipe(&board,10,10,0,2);
    pipe.initialize();
    EXPECT_FALSE(board.isPlaying());
    EXPECT_EQ(0,board.getVolume());
}

TEST(OutflowPipeTests, Start_ShouldRampVolumeUp) {
    TestBoard board;
    OutflowPipe pipe(&board,10,10,0,2);
    pipe.initialize();
    pipe.tick(true);
    EXPECT_TRUE(board.isPlaying());
    EXPECT_EQ(10,board._volume);
    EXPECT_GT(board._volumeCalls,1);
}

TEST(OutflowPipeTests, Start_ShouldRampVolumeDown) {
    TestBoard board;
    OutflowPipe pipe(&board,10,10,0,2);
    pipe.initialize();
    pipe.tick(true);
    pipe.tick(false);
    EXPECT_FALSE(board.isPlaying());
    EXPECT_EQ(0,board._volume);
    EXPECT_GT(board._volumeCalls,1);
}

TEST(OutflowPipeTests, Start_ShouldMostlyPlayRegularTrack) {
    TestBoard board;
    int probability = 4;
    OutflowPipe pipe1(&board,10,10,0,probability);
    pipe1.initialize();
    pipe1.tick(true);
    EXPECT_EQ(1,board._playing);
    probability = 2;
    OutflowPipe pipe2(&board,10,10,0,probability);
    pipe2.initialize();
    pipe2.tick(true);
    EXPECT_EQ(1,board._playing);
}

TEST(OutflowPipeTests, Start_ShouldPlayEasterEgg) {
    TestBoard board;
    int probability = 3;
    OutflowPipe pipe1(&board,10,10,0,probability);
    pipe1.initialize();
    pipe1.tick(true);
    EXPECT_EQ(2,board._playing);
}

TEST(OutflowPipeTests, ShouldStartOnlyOnce) {
    TestBoard board;
    OutflowPipe pipe(&board,10,10,0,2);
    pipe.initialize();
    pipe.tick(true);
    pipe.tick(true);
    EXPECT_EQ(1,board._playCalls);
}

TEST(OutflowPipeTests, ShouldStopOnlyOnce) {
    TestBoard board;
    OutflowPipe pipe(&board,10,10,0,2);
    pipe.initialize();
    int initialStopCalls = board._stopCalls;
    pipe.tick(true);
    pipe.tick(false);
    pipe.tick(false);
    EXPECT_EQ(1 + initialStopCalls,board._stopCalls);
}
