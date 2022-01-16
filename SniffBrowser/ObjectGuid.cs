using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SniffBrowser
{
    public enum HighGuid
    {
        Item          = 0x4000,                       // blizz 4000
        Container     = 0x4000,                       // blizz 4000
        Player        = 0x0000,                       // blizz 0000
        GameObject    = 0xF110,                       // blizz F110
        Transport     = 0xF120,                       // blizz F120 (for GAMEOBJECT_TYPE_TRANSPORT)
        Creature      = 0xF130,                       // blizz F130
        Pet           = 0xF140,                       // blizz F140
        DynamicObject = 0xF100,                       // blizz F100
        Corpse        = 0xF101,                       // blizz F100
        MoTransport   = 0x1FC0,                       // blizz 1FC0 (for GAMEOBJECT_TYPE_MO_TRANSPORT)
    };

    public enum ObjectType
    {
        Object        = 0,
        Item          = 1,
        Container     = 2,
        Creature      = 3,
        Player        = 4,
        GameObject    = 5,
        DynamicObject = 6,
        Corpse        = 7
    };

    public class ObjectGuid : IEquatable<ObjectGuid>
    {
        public ulong RawGuid { get; protected set; }

        public static ObjectGuid Empty = new ObjectGuid(0);

        public ObjectGuid(ulong id)
        {
            RawGuid = id;
        }

        public bool HasEntry()
        {
            switch (GetHighType())
            {
                case HighGuid.Item:
                case HighGuid.Player:
                case HighGuid.DynamicObject:
                case HighGuid.Corpse:
                case HighGuid.MoTransport:
                return false;
                case HighGuid.GameObject:
                case HighGuid.Transport:
                case HighGuid.Creature:
                case HighGuid.Pet:
                default:
                return true;
            }
        }

        public uint GetCounter()
        {
            return HasEntry()
                ? (uint)(RawGuid & (0x0000000000FFFFFFul))
                : (uint)(RawGuid & (0x00000000FFFFFFFFul));
        }
        public uint GetEntry()
        {
            return HasEntry()
                ? (uint)((RawGuid >> 24) & (0x0000000000FFFFFFul))
                : 0;
        }

        public HighGuid GetHighType()
        {
            return (HighGuid)((RawGuid >> 48) & 0x0000FFFF);
        }

        public ObjectType GetObjectType()
        {
            switch (GetHighType())
            {
                case HighGuid.Player:
                return ObjectType.Player;
                case HighGuid.DynamicObject:
                return ObjectType.DynamicObject;
                case HighGuid.Item:
                return ObjectType.Item;
                case HighGuid.GameObject:
                case HighGuid.Transport:
                case HighGuid.MoTransport:
                return ObjectType.GameObject;
                case HighGuid.Creature:
                case HighGuid.Pet:
                return ObjectType.Creature;
                default:
                return ObjectType.Object;
            }
        }

        public static bool operator ==(ObjectGuid first, ObjectGuid other)
        {
            if (ReferenceEquals(first, other))
                return true;

            if (((object)first == null) || ((object)other == null))
                return false;

            return first.Equals(other);
        }

        public static bool operator !=(ObjectGuid first, ObjectGuid other)
        {
            return !(first == other);
        }

        public override bool Equals(object obj)
        {
            return obj is ObjectGuid && Equals((ObjectGuid)obj);
        }

        public bool Equals(ObjectGuid other)
        {
            return other.RawGuid == RawGuid;
        }

        public override int GetHashCode()
        {
            return new { RawGuid }.GetHashCode();
        }
        public bool IsEmpty()
        {
            return RawGuid == 0;
        }

        public override string ToString()
        {
            if (IsEmpty())
                return "None";

            string str = GetObjectType().ToString() + " (";
            if (HasEntry())
                str += "Entry: " + GetEntry().ToString() + " ";
            str += "Guid: " + GetCounter().ToString() + ")";

            return str;
        }
    }
}
