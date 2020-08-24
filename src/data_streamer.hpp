//
// Created by Ryan Elliott on 8/14/20.
//

#ifndef SUCCESSOR_DATA_STREAMER_HPP
#define SUCCESSOR_DATA_STREAMER_HPP


#include <ludere/candlestick_data.hpp>
#include <ludere/data_streamable.hpp>
#include <ParseCSV/csv.h>

// TODO: Design multiple ticker streaming support. Ludere supports this, however the demo code does not display this
class data_streamer : public lud::data_streamable
{
public:
    explicit data_streamer(std::string filename_)
            : m_filename(std::move(filename_)), m_file(io::CSVReader<6>(m_filename))
    {
        m_file.read_header(io::ignore_extra_column, "timestamp", "open", "high", "low", "close", "volume");
    }

    explicit data_streamer(std::string_view filename_)
            : m_filename(filename_), m_file(io::CSVReader<6>(m_filename))
    {
        m_file.read_header(io::ignore_extra_column, "timestamp", "open", "high", "low", "close", "volume");
    }

    std::unordered_map<std::string, lud::candlestick_data> poll_next_stream() override
    {
        std::string timestamp_;
        float open_, high_, low_, close_;
        uint32_t volume_;
        if (readNextRow(timestamp_, open_, high_, low_, close_, volume_)) {
            lud::candlestick_data candle_("AAPL", data_streamer::time_t_from_string(timestamp_), open_, high_, low_,
                                          close_, volume_);
            return std::unordered_map<std::string, lud::candlestick_data>{std::make_pair(candle_.m_ticker, candle_)};
        }

        return std::unordered_map<std::string, lud::candlestick_data>{};
    }

    bool readNextRow(std::string &timestamp, float &open, float &high, float &low, float &close, uint32_t &volume)
    {
        try {
            m_file.read_row(timestamp, open, high, low, close, volume);
            return !timestamp.empty();
        } catch (const io::error::no_digit &e) {
            LUD_WARN("Error parsing CSV row (io::error::no_digit), continuing to next: %s", e.what());
            return readNextRow(timestamp, open, high, low, close, volume);
        } catch (...) {
            return false;
        }
    }

    /**
     * Timestamps are in an irregular format (2019-08-19 09:30:00-04:00). Convert to boost-supported ISO8601
     * (20190819T09:30:00.000000). This may be my misunderstanding, but true ISO8601 is (2019-08-19T09:30:00.000000)
     * @param tmp String of format 2020-08-18 09:30:00-04:00
     * @return time_t (seconds since Unix epoch)
     */
    static time_t time_t_from_string(std::string tmp)
    {
        std::string timestamp_;
        const std::string delim_ = "-";
        size_t pos_ = 0;
        while ((pos_ = tmp.find(delim_)) != std::string::npos) {
            timestamp_ += tmp.substr(0, pos_);
            tmp.erase(0, pos_ + delim_.length());
        }
        std::replace_if(timestamp_.begin(), timestamp_.end(), [](const char c) { return c == ' '; }, 'T');
        timestamp_.erase(std::remove_if(timestamp_.begin(), timestamp_.end(), [](const char c) { return c == ':'; }));
        auto ptime_ = boost::date_time::parse_iso_time<boost::posix_time::ptime>(timestamp_, 'T');
        return boost::lexical_cast<time_t>(to_time_t(ptime_));
    }

    inline static time_t to_time_t(boost::posix_time::ptime t_)
    {
        boost::posix_time::ptime epoch_(boost::gregorian::date(1970, 1, 1));
        return time_t((t_ - epoch_).total_seconds());
    }

private:
    const std::string m_filename;
    io::CSVReader<6> m_file;
};


#endif //SUCCESSOR_DATA_STREAMER_HPP
