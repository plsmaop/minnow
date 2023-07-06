#include <algorithm>
#include <stdexcept>

#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ), buf_( capacity_, ' ' ) {}

void Writer::push( const string_view data )
{
  // Your code here.
  const auto gap = writer().available_capacity();
  if ( gap == 0 || data.empty() ) [[unlikely]] {
    return;
  }

  const auto start = pushed_ % capacity_;
  const auto push_cnt = gap > data.size() ? data.size() : gap;
  const auto first_part = min( capacity_ - start, push_cnt );

  std::copy( data.begin(), data.begin() + first_part, buf_.begin() + static_cast<std::ptrdiff_t>( start ) );
  if ( first_part < push_cnt ) {
    std::copy( data.begin() + first_part, data.begin() + push_cnt, buf_.begin() );
  }

  pushed_ += push_cnt;
}

void Writer::close()
{
  // Your code here.
  closed_ = true;
}

void Writer::set_error()
{
  // Your code here.
  error_ = true;
}

bool Writer::is_closed() const
{
  // Your code here.
  return closed_;
}

uint64_t Writer::available_capacity() const
{
  // Your code here.
  return capacity_ - ( pushed_ - poped_ );
}

uint64_t Writer::bytes_pushed() const
{
  // Your code here.
  return pushed_;
}

string_view Reader::peek() const
{
  // Your code here.
  const auto gap = pushed_ - poped_;
  if ( gap == 0 ) [[unlikely]] {
    return {};
  }

  const auto start = poped_ % buf_.size();
  const auto peek_cnt = min( capacity_ - start, gap );

  return { &buf_[start], peek_cnt };
}

bool Reader::is_finished() const
{
  // Your code here.
  return closed_ && pushed_ == poped_;
}

bool Reader::has_error() const
{
  // Your code here.
  return error_;
}

void Reader::pop( uint64_t len )
{
  const auto gap = pushed_ - poped_;
  poped_ += gap > len ? len : gap;
}

uint64_t Reader::bytes_buffered() const
{
  // Your code here.
  return pushed_ - poped_;
}

uint64_t Reader::bytes_popped() const
{
  // Your code here.
  return poped_;
}
