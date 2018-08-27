/*
	File:  AVAudioPlayer.h
	
	Framework:  AVFoundation
 
	Copyright 2008-2016 Apple Inc. All rights reserved.
 */

#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVAudioFormat.h>
#import <Foundation/Foundation.h>
#import <AVFAudio/AVAudioSettings.h>

#if TARGET_OS_IPHONE
#import <AVFAudio/AVAudioSession.h>
#endif // #if TARGET_OS_EMBEDDED

#import <Availability.h>

NS_ASSUME_NONNULL_BEGIN

@class NSData, NSURL, NSError;
@class AVAudioSessionChannelDescription;
@protocol AVAudioPlayerDelegate;

NS_CLASS_AVAILABLE(10_7, 2_2) __WATCHOS_AVAILABLE(3_0)
@interface AVAudioPlayer : NSObject {
@private
    id _impl;
}

//参考自:http://www.cnblogs.com/kenshincui/p/4186022.html

/* For all of these init calls, if a return value of nil is given you can check outError to see what the problem was.
 If not nil, then the object is usable for playing
 */

/* all data must be in the form of an audio file understood by CoreAudio */
/*
 使用文件URL初始化播放器，注意这个URL不能是HTTP URL，AVAudioPlayer不支持加载网络媒体流，只能播放本地文件
 */
- (nullable instancetype)initWithContentsOfURL:(NSURL *)url error:(NSError **)outError;
/*
 使用NSData初始化播放器，注意使用此方法时必须文件格式和文件后缀一致，否则出错，所以相比此方法更推荐使用上述方法或- (instancetype)initWithData:(NSData *)data fileTypeHint:(NSString *)utiString error:(NSError **)outError方法进行初始化
 */
- (nullable instancetype)initWithData:(NSData *)data error:(NSError **)outError;

/* The file type hint is a constant defined in AVMediaFormat.h whose value is a UTI for a file format. e.g. AVFileTypeAIFF. */
/* Sometimes the type of a file cannot be determined from the data, or it is actually corrupt. The file type hint tells the parser what kind of data to look for so that files which are not self identifying or possibly even corrupt can be successfully parsed. */
- (nullable instancetype)initWithContentsOfURL:(NSURL *)url fileTypeHint:(NSString * __nullable)utiString error:(NSError **)outError NS_AVAILABLE(10_9, 7_0);
- (nullable instancetype)initWithData:(NSData *)data fileTypeHint:(NSString * __nullable)utiString error:(NSError **)outError NS_AVAILABLE(10_9, 7_0);

/* transport control */
/* methods that return BOOL return YES on success and NO on failure. */
/*
 加载音频文件到缓冲区，注意即使在播放之前音频文件没有加载到缓冲区程序也会隐式调用此方法
 */
- (BOOL)prepareToPlay;	/* get ready to play the sound. happens automatically on play. */
/**  播放音频文件  */
- (BOOL)play;			/* sound is played asynchronously. */
/**  在指定的时间开始播放音频  */
- (BOOL)playAtTime:(NSTimeInterval)time NS_AVAILABLE(10_7, 4_0); /* play a sound some time in the future. time is an absolute time based on and greater than deviceCurrentTime. */
/**  暂停播放  */
- (void)pause;			/* pauses playback, but remains ready to play. */
/**  停止播放  */
- (void)stop;			/* stops playback. no longer ready to play. */

/* properties */
/**  是否正在播放，只读  */
@property(readonly, getter=isPlaying) BOOL playing; /* is it playing or not? */
/**  音频声道数，只读  */
@property(readonly) NSUInteger numberOfChannels;
/**  音频时长  */
@property(readonly) NSTimeInterval duration; /* the duration of the sound. */

/* the delegate will be sent messages from the AVAudioPlayerDelegate protocol */
@property(assign, nullable) id<AVAudioPlayerDelegate> delegate;

/* one of these properties will be non-nil based on the init... method used */
/**  音频文件路径，只读  */
@property(readonly, nullable) NSURL *url; /* returns nil if object was not created with a URL */
/**  音频数据，只读  */
@property(readonly, nullable) NSData *data; /* returns nil if object was not created with a data object */
/**  立体声平衡，如果为-1.0则完全左声道，如果0.0则左右声道平衡，如果为1.0则完全为右声道  */
@property float pan NS_AVAILABLE(10_7, 4_0); /* set panning. -1.0 is left, 0.0 is center, 1.0 is right. */
@property float volume; /* The volume for the sound. The nominal range is from 0.0 to 1.0. */
/**  音量大小，范围0-1.0  */
- (void)setVolume:(float)volume fadeDuration:(NSTimeInterval)duration NS_AVAILABLE(10_12, 10_0); /* fade to a new volume over a duration */
/**  	是否允许改变播放速率  */
@property BOOL enableRate NS_AVAILABLE(10_8, 5_0); /* You must set enableRate to YES for the rate property to take effect. You must set this before calling prepareToPlay. */
//播放速率，范围0.5-2.0，如果为1.0则正常播放，如果要修改播放速率则必须设置enableRate为YES
@property float rate NS_AVAILABLE(10_8, 5_0); /* See enableRate. The playback rate for the sound. 1.0 is normal, 0.5 is half speed, 2.0 is double speed. */


/*  If the sound is playing, currentTime is the offset into the sound of the current playback position.
 If the sound is not playing, currentTime is the offset into the sound where playing would start. */
//当前播放时长
@property NSTimeInterval currentTime;

/* returns the current time associated with the output device */
//输出设备播放音频的时间，注意如果播放中被暂停此时间也会继续累加
@property(readonly) NSTimeInterval deviceCurrentTime NS_AVAILABLE(10_7, 4_0);

/* "numberOfLoops" is the number of times that the sound will return to the beginning upon reaching the end.
 A value of zero means to play the sound just once.
 A value of one will result in playing the sound twice, and so on..
 Any negative number will loop indefinitely until stopped.
 */
//循环播放次数，如果为0则不循环，如果小于0则无限循环，大于0则表示循环次数
@property NSInteger numberOfLoops;

/* settings */
// 音频播放设置信息，只读
@property(readonly) NSDictionary<NSString *, id> *settings NS_AVAILABLE(10_7, 4_0); /* returns a settings dictionary with keys as described in AVAudioSettings.h */

/* returns the format of the audio data */
@property(readonly) AVAudioFormat *format NS_AVAILABLE(10_12, 10_0);

/* metering */
//是否启用音频测量，默认为NO，一旦启用音频测量可以通过updateMeters方法更新测量值
@property(getter=isMeteringEnabled) BOOL meteringEnabled; /* turns level metering on or off. default is off. */
//更新音频测量值，注意如果要更新音频测量值必须设置meteringEnabled为YES，通过音频测量值可以即时获得音频分贝等信息
- (void)updateMeters; /* call to refresh meter values */
//获得指定声道的分贝峰值，注意如果要获得分贝峰值必须在此之前调用updateMeters方法
- (float)peakPowerForChannel:(NSUInteger)channelNumber; /* returns peak power in decibels for a given channel */
//获得指定声道的分贝平均值，注意如果要获得分贝平均值必须在此之前调用updateMeters方法
- (float)averagePowerForChannel:(NSUInteger)channelNumber; /* returns average power in decibels for a given channel */

#if TARGET_OS_IPHONE
/* The channels property lets you assign the output to play to specific channels as described by AVAudioSession's channels property */
/* This property is nil valued until set. */
/* The array must have the same number of channels as returned by the numberOfChannels property. */
//获得或设置播放声道
@property(nonatomic, copy, nullable) NSArray<AVAudioSessionChannelDescription *> *channelAssignments NS_AVAILABLE(10_9, 7_0); /* Array of AVAudioSessionChannelDescription objects */
#endif

@end

/* A protocol for delegates of AVAudioPlayer */
__WATCHOS_AVAILABLE(3_0)
@protocol AVAudioPlayerDelegate <NSObject>
@optional
/* audioPlayerDidFinishPlaying:successfully: is called when a sound has finished playing. This method is NOT called if the player is stopped due to an interruption. */
//音频播放完成
- (void)audioPlayerDidFinishPlaying:(AVAudioPlayer *)player successfully:(BOOL)flag;

/* if an error occurs while decoding it will be reported to the delegate. */
//音频解码发生错误
- (void)audioPlayerDecodeErrorDidOccur:(AVAudioPlayer *)player error:(NSError * __nullable)error;

#if TARGET_OS_IPHONE

/* AVAudioPlayer INTERRUPTION NOTIFICATIONS ARE DEPRECATED - Use AVAudioSession instead. */

/* audioPlayerBeginInterruption: is called when the audio session has been interrupted while the player was playing. The player will have been paused. */
- (void)audioPlayerBeginInterruption:(AVAudioPlayer *)player NS_DEPRECATED_IOS(2_2, 8_0);

/* audioPlayerEndInterruption:withOptions: is called when the audio session interruption has ended and this player had been interrupted while playing. */
/* Currently the only flag is AVAudioSessionInterruptionFlags_ShouldResume. */
- (void)audioPlayerEndInterruption:(AVAudioPlayer *)player withOptions:(NSUInteger)flags NS_DEPRECATED_IOS(6_0, 8_0);

- (void)audioPlayerEndInterruption:(AVAudioPlayer *)player withFlags:(NSUInteger)flags NS_DEPRECATED_IOS(4_0, 6_0);

/* audioPlayerEndInterruption: is called when the preferred method, audioPlayerEndInterruption:withFlags:, is not implemented. */
- (void)audioPlayerEndInterruption:(AVAudioPlayer *)player NS_DEPRECATED_IOS(2_2, 6_0);

#endif // TARGET_OS_IPHONE

@end

NS_ASSUME_NONNULL_END
