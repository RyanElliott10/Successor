//
// Created by Ryan Elliott on 8/14/20.
//

#ifndef SUCCESSOR_DATASTREAMER_HPP
#define SUCCESSOR_DATASTREAMER_HPP


#include <ludere/CandlestickData.hpp>
#include <ludere/IDataStreamer.hpp>
#include <ParseCSV/csv.h>

// TODO: Design multiple ticker streaming support. Ludere supports this, however the demo code does not display this
class DataStreamer : public lud::IDataStreamer
{
public:
    explicit DataStreamer(std::string filename)
            : m_filename(std::move(filename)), m_file(io::CSVReader<6>(m_filename))
    {
        m_file.read_header(io::ignore_extra_column, "timestamp", "open", "high", "low", "close", "volume");
    }

    explicit DataStreamer(std::string_view filename)
            : m_filename(filename), m_file(io::CSVReader<6>(m_filename))
    {
        m_file.read_header(io::ignore_extra_column, "timestamp", "open", "high", "low", "close", "volume");
    }

    std::unordered_map<std::string, lud::CandlestickData> pollNextStream() override
    {
        std::string timestamp;
        float open, high, low, close;
        uint32_t volume;
        if (readNextRow(timestamp, open, high, low, close, volume)) {
            lud::CandlestickData candle("TSLA", DataStreamer::time_t_from_string(timestamp), open, high, low, close, volume);
            std::cout << candle << std::endl;
            return std::unordered_map<std::string, lud::CandlestickData> { std::make_pair(candle.ticker, candle) };
        }

        return std::unordered_map<std::string, lud::CandlestickData>{};
    }

    bool readNextRow(std::string &timestamp, float &open, float &high, float &low, float &close, uint32_t &volume) {
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
        std::string _timestamp;
        const std::string delim = "-";
        size_t _pos = 0;
        while ((_pos = tmp.find(delim)) != std::string::npos) {
            _timestamp += tmp.substr(0, _pos);
            tmp.erase(0, _pos + delim.length());
        }
        std::replace_if(_timestamp.begin(), _timestamp.end(), [](const char c) { return c == ' '; }, 'T');
        _timestamp.erase(
                std::remove_if(_timestamp.begin(), _timestamp.end(), [](const char c) { return c == ':'; }));
        auto ptime = boost::date_time::parse_iso_time<boost::posix_time::ptime>(_timestamp, 'T');
        return boost::lexical_cast<time_t>(to_time_t(ptime));
    }

    inline static time_t to_time_t(boost::posix_time::ptime t)
    {
        boost::posix_time::ptime epoch(boost::gregorian::date(1970, 1, 1));
        return time_t((t - epoch).total_seconds());
    }

private:
    const std::string m_filename;
    io::CSVReader<6> m_file;
};


#endif //SUCCESSOR_DATASTREAMER_HPP
