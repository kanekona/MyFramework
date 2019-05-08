#include "MediaPlayer.h"

MediaPlayer::MediaPlayer()
	:Sprite(true)
{
	format_context = nullptr;
}
MediaPlayer::~MediaPlayer()
{

}
void MediaPlayer::Load(const std::string& path)
{
	//非推奨初期化関数
	//avcodec_register_all();
	//av_register_all();
	//avfilter_register_all();

	avformat_open_input(&format_context, path.c_str(), nullptr, nullptr);
	avformat_find_stream_info(format_context, nullptr);
	
}
void MediaPlayer::Update()
{

}