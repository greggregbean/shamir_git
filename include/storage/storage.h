#ifndef STORAGE_H
#define STORAGE_H

#include <filesystem>
#include <functional>
#include <sstream>
#include <string_view>

namespace shagit {

namespace fs = std::filesystem;

/**
 * Storage structure:
 *
 *  Storage Dir:
 * |
 * |     (Proj ID)            (Proj Name)
 * ----- 983912839182391283 - Shamir - Project src tree
 * |                          |
 * |                          |
 * |                          ----- METAFILE
 * |                          |
 * |                          |
 * |                          ----- ChangeRequests
 * |                          |     |
 * |                          |     |
 * |                          |     ----- cr_1 - CR src tree
 * |                          |     |
 * |                          |     |
 * |                          |     ----- cr_2
 * |                          |
 * |                          ----- ParticipantRequests
 * |                                |
 * |                                |
 * |                                ----- pr_1
 * |                                |
 * |                                |
 * |                                ----- pr_2
 * |
 * ----- 912391293123812312 - proj2
 * |
 * |
 * ----- 123123123412412323 - proj3
 *
 *
 *
 * METAFILE:
 *      Project name: Shamir
 *      Project Id: 983912839182391283
 *      Secret: 78123
 *      Access number: 2
 *      Owner:
 *          Name: Zinin Ivan
 *          Mail: zinin.ia@phystech.edu
 *      Participants:
 *          Name: Kitaev Konstantin
 *          Mail: kitaev.kn@phystech.edu
 *
 *
 *
 * PR_ID:
 *      Participant:
 *          Name:
 *          Mail:
 */

struct ParticipantInfo {
    std::string name;
    std::string mail;
};

struct HubInfo {
    std::string proj_name;
    int64_t secret;
    size_t access_number;
    ParticipantInfo owner;
    std::vector<ParticipantInfo> participants;
};

class HubStorage {
public:
    using Id = uint64_t;
    using DirEntry = fs::directory_entry;
    using StorageVisitor = std::function<void(fs::path, const DirEntry&)>;

    static constexpr std::string_view STORAGE_DIR_VAR = "STORAGE_DIR";
    static constexpr std::string_view CR_DIR_VAR = "CR_DIR";
    static constexpr std::string_view CHANGE_REQ = "ChangeRequests";
    static constexpr std::string_view PARTICIPANTS_REQ = "ParticipantsRequests";
    static constexpr std::string_view METAFILE = "METAINFO";

    static constexpr std::string_view SECRET = "Shamir Secret: ";
    static constexpr std::string_view OWNER = "Owner:";
    static constexpr std::string_view NAME = "Name: ";
    static constexpr std::string_view MAIL = "Mail: ";

    explicit HubStorage();

    void ListHubs(std::stringstream& ss);
    std::vector<Id> CreateHub(const HubInfo& proj_info);
    Id JoinHub(Id proj_id, const ParticipantInfo& participant);
    void ApproveJoin(Id proj_id, Id pr_id);
    // Id CreateCR(Id proj_id, ...);
    void ApproveCR(Id cr_id);

    bool CheckSecret(Id hub_id, int64_t secret);
    ParticipantInfo GetOwner(Id hub_id);
    ParticipantInfo GetParticipant(Id hub_id, Id pr_id);

    void TraverseStorage(const StorageVisitor& visitor);

private:
    Id GenerateId(const std::string& src);

    DirEntry storage_dir_;
};

class DirGuard {
    fs::path path_;

public:
    DirGuard() : path_(fs::current_path()) {}
    ~DirGuard() { fs::current_path(path_); }
};

} // namespace shagit

#endif // STORAGE_H
