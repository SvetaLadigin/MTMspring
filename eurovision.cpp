#include <utility>

#include "eurovision.h"

#include <string.h>

using std::endl;

static string voter_type_to_string(VoterType type)
{
    switch(type)
    {
        case Regular:
            return "Regular";
        case Judge:
            return "Judge";
        case All:
            return "All";
    }
    return "Unknown";
}

static string phase_to_string(Phase phase)
{
    switch(phase)
    {
        case Registration:
            return "Registration";
        case Contest:
            return "Contest";
        case Voting:
            return "Voting";
    }
    return "Unknown";
}

Participant::Participant(const string &state, const string &song, int song_len, const string &singer)
   : m_state(state), m_song(song), m_song_len(song_len), m_singer(singer), m_is_registered(false)
{}


void Participant::update(const string &new_song_name, int new_song_len, const string &new_singer)
{
    if(this->isRegistered())
        return;

    if(!new_song_name.empty()) {
        this->m_song = new_song_name;
    }
    if(!new_singer.empty()) {
        this->m_singer = new_singer;
    }
    if(new_song_len > 0) {
        this->m_song_len = new_song_len;
    }
}

string Participant::state() const
{
    return this->m_state;
}

string Participant::song() const
{
    return this->m_song;
}

int Participant::timeLength() const
{
    return this->m_song_len;
}

string Participant::singer() const
{
    return this->m_singer;
}

bool Participant::isRegistered() const
{
    return this->m_is_registered;
}

void Participant::updateRegistered(bool value)
{
    this->m_is_registered = value;
}

ostream& operator<<(ostream& o, const Participant& p)
{
    o << '[' << p.state() << '/' << p.song() << '/' << p.timeLength() << '/' << p.singer() << ']';
    return o;
}

Voter::Voter(const string &state, VoterType type)
    : m_state(state), m_type(type), m_voted_count(0)
{}

string Voter::state() const {
    return this->m_state;
}

VoterType Voter::voterType() const {
    return this->m_type;
}

void Voter::operator--()
{
    --this->m_voted_count;
}

void Voter::operator++()
{
    ++this->m_voted_count;
}

int Voter::timesOfVotes() const {
    return m_voted_count;
}

ostream& operator<<(ostream& o, const Voter& v)
{
    o << '<' << v.state() << '/' << voter_type_to_string(v.voterType()) << '>';
    return o;
}

void setVoteState(Vote &v, int i, const string &state)
{
    if(state.empty()) {
        return;
    }
    v.m_state[i] = state;
    v.m_number_of_votes++;
}

Vote::Vote(Voter &voter, const string &state1, const string &state2,
           const string &state3, const string &state4,
           const string &state5, const string &state6,
           const string &state7, const string &state8,
           const string &state9, const string &state10)
        : m_voter(voter), m_number_of_votes(0) {
    setVoteState(*this, 0, state1);
    if(this->m_voter.voterType() == Regular) {
        return;
    }
    setVoteState(*this, 1, state2);
    setVoteState(*this, 2, state3);
    setVoteState(*this, 3, state4);
    setVoteState(*this, 4, state5);
    setVoteState(*this, 5, state6);
    setVoteState(*this, 6, state7);
    setVoteState(*this, 7, state8);
    setVoteState(*this, 8, state9);
    setVoteState(*this, 9, state10);
}

MainControl::MainControl(int max_song_len, int max_participants, int max_regular_votes)
    : m_phase(Registration), m_max_song_len(max_song_len),
    m_max_participants(max_participants), m_max_regular_votes(max_regular_votes),
    m_participants()
{}

void MainControl::setPhase(Phase new_phase)
{
    if(new_phase != this->m_phase + 1)
        return;

    this->m_phase = new_phase;
}

Phase MainControl::phase() const
{
    return m_phase;
}

bool MainControl::legalParticipant(const Participant &p) const
{
    return p.timeLength() <= this->m_max_song_len &&
           p.state().length() && p.song().length() && p.singer().length();
}

bool MainControl::participate(const string &state) const
{
    return m_participants.getParticipantNode(state) != nullptr;
}

MainControl &MainControl::operator+=(Participant &p)
{
    if(this->m_phase != Registration ||
       this->m_participants.length() > this->m_max_participants ||
       !this->legalParticipant(p) ||
       this->participate(p.state())) {
        return *this;
    }

    this->m_participants.add(p);
    p.updateRegistered(true);

    return *this;
}

MainControl &MainControl::operator-=(Participant &p)
{
    if(this->m_phase != Registration || !p.isRegistered()) {
        return *this;
    }

    this->m_participants.remove(p);
    p.updateRegistered(false);

    return *this;
}


bool MainControl::legalVote(const Vote &v) const
{
    if(v.m_number_of_votes == 0)
        return false;
    if(!this->participate(v.m_voter.state()))
        return false;

    int max_votes_count = v.m_voter.voterType() == Regular ? this->m_max_regular_votes : 1;
    return v.m_voter.timesOfVotes() < max_votes_count;
}

int get_judge_score_for_rank(int i)
{
    if(i < 3) {
        return 12 - i * 2;
    }
    return 10 - i;
}

MainControl &MainControl::operator+=(Vote &&v)
{
    Vote &v_ref = v;
    (*this) += v_ref;

    return *this;
}

MainControl &MainControl::operator+=(const Vote &v)
{
    if(this->m_phase != Voting ||
       !this->legalVote(v)) {
        return *this;
    }

    // A judge can vote once even if all of the votes are illegal
    if(v.m_voter.voterType() == Judge) {
        ++v.m_voter;
    }

    for(int i = 0; i < v.m_number_of_votes; ++i) {
        ParticipantNode *node = m_participants.getParticipantNode(v.m_state[i]);
        if(node == nullptr) {
            continue;
        }
        const Participant &participant = node->participant;
        if(participant.state() == v.m_voter.state())
            continue;

        if(v.m_voter.voterType() == Regular) {
            ++v.m_voter;
            node->regular_votes++;
        } else {
            node->judge_votes += get_judge_score_for_rank(i);
        }
    }

    return *this;
}


void MainControl::printRegistrationStep(ostream &o) const
{
    for(const ParticipantNode *node = m_participants.begin(); node != nullptr; node = node->next()) {
        o << node->participant << endl;
    }
}

void MainControl::printContestStep(ostream &o) const
{
}

void MainControl::printVotingStep(ostream &o) const
{
    for(const ParticipantNode *node = m_participants.begin(); node != nullptr; node = node->next())
    {
        o << node->participant.state() << " : Regular(" << node->regular_votes << ") Judge("
        << node->judge_votes << ")" << endl;
    }
}

ostream &operator<<(ostream &o, const MainControl &eurovision) {
    o << '{' << endl << phase_to_string(eurovision.phase()) << endl;
    switch(eurovision.phase()) {
        case Registration:
            eurovision.printRegistrationStep(o);
            break;
        case Contest:
            eurovision.printContestStep(o);
            break;
        case Voting:
            eurovision.printVotingStep(o);
            break;
    }
    o << '}' << endl;
    return o;
}

MainControl::ParticipantNode::ParticipantNode(const Participant &participant)
    : m_next(nullptr), participant(participant), regular_votes(0), judge_votes(0)
{
}

MainControl::ParticipantNode::~ParticipantNode()
{
    delete this->m_next;
}

const MainControl::ParticipantNode *MainControl::ParticipantNode::next() const
{
    return m_next;
}

MainControl::ParticipantNode *MainControl::ParticipantNode::next()
{
    return m_next;
}

MainControl::ParticipantsList::ParticipantsList()
    : m_head(nullptr), m_length(0)
{}

MainControl::ParticipantsList::~ParticipantsList(){
    delete m_head;
}

int MainControl::ParticipantsList::compareParticipants(const Participant &p1, const Participant &p2) {
    return p1.state().compare(p2.state());
}

void MainControl::ParticipantsList::add(const Participant &participant)
{
    ParticipantNode* node = new ParticipantNode(participant);
    ParticipantNode* current;

    /* Special case for the head end */
    if (m_head == nullptr || compareParticipants(m_head->participant, node->participant) > 0)
    {
        node->m_next = m_head;
        m_head = node;
    }
    else
    {
        /* Locate the node before the point of insertion */
        current = m_head;
        while (current->m_next != nullptr &&
                compareParticipants(current->m_next->participant, node->participant) < 0)
        {
            current = current->m_next;
        }
        node->m_next = current->m_next;
        current->m_next = node;
    }
    this->m_length++;
}

void MainControl::ParticipantsList::remove(const Participant &participant)
{
    ParticipantNode *prev_node = m_head;
    if(m_head->participant.state() == participant.state()) {
        m_head = m_head->m_next;
        prev_node->m_next = nullptr;
        delete prev_node;
        return;
    }
    ParticipantNode *node = m_head->m_next;
    while(node != nullptr) {
        if (node->participant.state() == participant.state())
        {
            prev_node->m_next = node->m_next;
            node->m_next = nullptr;
            delete node;
            this->m_length--;
            break;
        }
        prev_node = node;
        node = node->m_next;
    }
}
MainControl::ParticipantNode *MainControl::ParticipantsList::getParticipantNode(const string &state)
{
    for(ParticipantNode *node = this->begin(); node != nullptr; node = node->next()) {
        if(node->participant.state() == state) {
            return node;
        }
    }
    return nullptr;
}

const MainControl::ParticipantNode *MainControl::ParticipantsList::getParticipantNode(const string &state) const
{
    return const_cast<MainControl::ParticipantsList*>(this)->getParticipantNode(state);
}

MainControl::ParticipantNode *MainControl::ParticipantsList::begin()
{
    return m_head;
}

const MainControl::ParticipantNode *MainControl::ParticipantsList::begin() const
{
    return m_head;
}

int MainControl::ParticipantsList::length() const
{
    return m_length;
}

