using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SniffBrowser
{
    public static class Utility
    {
        private static readonly DateTime Epoch = new DateTime(1970, 1, 1, 0, 0, 0, DateTimeKind.Utc);

        public static DateTime GetDateTimeFromUnixTime(double unixTime)
        {
            return Epoch.AddSeconds(unixTime);
        }

        public static DateTime GetDateTimeFromUnixTimeMs(double unixTime)
        {
            return Epoch.AddMilliseconds(unixTime);
        }

        public static double GetUnixTimeFromDateTime(DateTime time)
        {
            return (time.ToUniversalTime() - Epoch.ToUniversalTime()).TotalSeconds;
        }

        public static double GetUnixTimeMsFromDateTime(DateTime time)
        {
            return (time.ToUniversalTime() - Epoch.ToUniversalTime()).TotalMilliseconds;
        }
    }
}
