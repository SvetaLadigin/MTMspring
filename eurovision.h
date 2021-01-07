#ifndef EUROVISION_H_
#define EUROVISION_H_

#include <iostream>

using std::string;
using std::ostream;

// it's allowed to define here any using statements, according to needs.
// do NOT define here : using namespace std;

//---------------------------------------------------

enum VoterType { All, Regular, Judge };
enum Phase { Registration, Contest, Voting };

//---------------------------------------------------

class Participant
{
// relevant private members can be defined here, if necessary.
    string m_state;
    string m_song;
    int m_song_len;
    string m_singer;
    bool m_is_registered;

public :
// need to define here possibly c'tr and d'tr and ONLY methods that
// are mentioned and demonstrated in the test example that has been published.
// NO OTHER METHODS SHOULD APPEAR HERE.

    Participant(const string &state, const string &song, int song_len, const string &singer);

    // Cannot use default and copy constructor
    Participant() = delete;
    Participant(Participant &p) = delete;
    void operator=(const Participant&) = delete;

    void update(const string &new_song_name, int new_song_len, const string &new_singer);
    void updateRegistered(bool value);

    string state() const;
    string song() const;
    int timeLength() const;
    string singer() const;
    bool isRegistered() const;
// NO friend is allowed here.

};

ostream& operator<<(ostream& o, const Participant& b);

//---------------------------------------------------


class Voter
{
// relevant private members can be defined here, if necessary.
    string m_state;
    VoterType m_type;
    int m_voted_count;

public :
    explicit Voter(const string &state, VoterType type=Regular);

    Voter() = delete;
    Voter(Voter &p) = delete;
    void operator=(const Voter&) = delete;

    string state() const;
    VoterType voterType() const;
    int timesOfVotes() const;

    void operator++();
    void operator--();

// need to define here possibly c'tr and d'tr and ONLY methods that
// are mentioned and demonstrated in the test example that has been published.
// NO OTHER METHODS SHOULD APPEAR HERE.

// NO friend is allowed here.

};

ostream& operator<<(ostream& o, const Voter& v);

// -----------------------------------------------------------

#define MAX_VOTE_STATES 10

struct Vote
{
// ALL is public here.
// need to define ONLY data members and c'tr and d'tr.
// NO NEED to define anything else.
    Vote(Voter &voter, const string &state1, const string &state2={},
            const string &state3={}, const string &state4={},
         const string &state5={}, const string &state6={},
         const string &state7={}, const string &state8={},
         const string &state9={}, const string &state10={});

    Voter &m_voter;
    string m_state[MAX_VOTE_STATES];
    int m_number_of_votes;
};

// -----------------------------------------------------------

#define DEFAULT_SONG_LEN 180
#define DEFAULT_MAX_PARTICIPANTS 26
#define DEFAULT_MAX_REGULAR_VOTES 5

class MainControl
{
// relevant private members can be defined here, if necessary.
    Phase m_phase;

    int m_max_song_len;
    int m_max_participants;
    int m_max_regular_votes;

    class ParticipantsList;

    class ParticipantNode
    {
        ParticipantNode *m_next;

    public:
        const Participant &participant;
        int regular_votes;
        int judge_votes;

        explicit ParticipantNode(const Participant &participant);
        ~ParticipantNode();

        ParticipantNode* next();
        const ParticipantNode* next() const;

        friend ParticipantsList;
    };

    class ParticipantsList
    {
    private:
        ParticipantNode* m_head;
        int m_length;

        static int compareParticipants(const Participant &p1, const Participant &p2);
    public:

        ParticipantsList();
        ~ParticipantsList();
        void add(const Participant &participant);
        void remove(const Participant &participant);

        ParticipantNode *getParticipantNode(const string &state);
        const ParticipantNode *getParticipantNode(const string &state) const;

        ParticipantNode *begin();
        const ParticipantNode *begin() const;
        int length() const;
    };

    ParticipantsList m_participants;

    bool legalVote(const Vote &v) const;

    void printRegistrationStep(ostream &o) const;
    void printContestStep(ostream &o) const;
    void printVotingStep(ostream &o) const;

    friend ostream& operator<<(ostream& o, const MainControl& eurovision);
public :
    explicit MainControl(int max_song_len=DEFAULT_SONG_LEN, int max_participants=DEFAULT_MAX_PARTICIPANTS,
            int max_regular_votes=DEFAULT_MAX_REGULAR_VOTES);
// need to define here possibly c'tr and d'tr and ONLY methods that
// are mentioned and demonstrated in the test example that has been published.
// NO OTHER METHODS SHOULD APPEAR HERE.

    void setPhase(Phase new_phase);

    Phase phase() const;

    bool legalParticipant(const Participant &p) const;
    bool participate(const string &state) const;

    MainControl& operator+=(Participant &p);
    MainControl& operator-=(Participant &p);

    MainControl& operator+=(Vote &&v);
    MainControl& operator+=(const Vote &v);
// Also it's allowed here to define friend.
};

ostream& operator<<(ostream& o, const MainControl& eurovision);

// -----------------------------------------------------------

#endif
