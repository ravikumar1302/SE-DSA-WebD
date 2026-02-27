# AEM Workflows

1. What Are Workflows?
    - Whenever there is requirement to automate repeated tasks (like compressing images) or tasks which need collaboration (like review and approval process), then we choose to implement it with AEM Workflows.

<img src="../Images/AEM_Workflow_Common_Use_Case.png" alt="AEM Workflow Common Use Case" width="40%" style="display: block; margin: auto;"><br>

    -   The diagram shows the flow for a review and approval process:
        -   Author User Group: The process starts with an "Author User Group."
        -   Author (Author the Page): An author from this group creates or edits a page.
        -   AEM Page: The author submits the page for approval.
        -   Approver (Review & Approve): The page is then sent to an "Approver."
        -   Reviewer User Group: The approver belongs to a "Reviewer User Group."
        -   Approval Outcome: The approver either approves the page (which goes back to the AEM page, likely to be published) or sends it back for revision (implied by the two-way arrow).

2.
